#include "stdafx.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::Connect()
{

	socket = std::shared_ptr<tcp::socket>(new tcp::socket(io_service));
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(getServerIP()), port);

	socket->connect(endpoint);
}
//! Gets integer values from the string
int GetGameInfo(std::string message)
{
	std::string::size_type sz;
	std::string number = "                       ";
	//Number of players
	for (int i = 0; i < message.size(); i++)
	{
		if (message[i] == *"[" && message[i + 1] == *"#" && message[i + 2] == *":")
		{
			for (int j = 0; j < 10; j++)
			{
				if (message[i + 3 + j] == *"]" && message[i + 4 + j] == *".")
					break;
				number[j] = message[i + 3 + j];

			}
			number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
			int num = std::stoi(number, &sz);
			if (num < 40)
				return num;
		}
	}
}
//! main netwrok update function
void NetworkManager::NetworkUpdate(Level& level, AgentManager& agentManager)
{
	std::string name = localPlayerName;
	std::string playerPosition = "X:" + std::to_string(agentManager.allAgents[agentManager.GetAgentNumberFomID(localPlayerName)].getX()) + ".Y:" + std::to_string(agentManager.allAgents[agentManager.GetAgentNumberFomID(localPlayerName)].getY()) + ".";

	sendTCPMessage("{<" + localPlayerName + "> " + playerPosition + "}\n");
	// process the list of players
	std::string updateMessage = RecieveMessage();
	ProcessArrayOfPlayerLocations(updateMessage, level, agentManager);
	//ProcessPlayerLocations(updateMessage, level, agentManager);


}


void NetworkManager::runMultiThread(Level& level, AgentManager& agentManager)
{
	//std::thread readerThread;
	//boost::thread_group g;
	//g.create_thread(&NetworkManager::RecieveMessage);
	//g.join_all();
	//std::thread t2(this);
	//some_threads.push_back(t2);
	//std::string receiveMessage = RecieveMessage();
	//ProcessArrayOfPlayerLocations(receiveMessage, level, agentManager);

	//boost::thread_group g;
	//g.create_thread(&NetworkManager::RecieveMessage);
	//boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	//g.create_thread([] { &NetworkManager::RecieveMessage; });
}


//! Returns whether the player exists in the list of players
bool DoesPlayerExist(std::vector<std::string>& playerNames, std::string playername)
{
	// Return true if theres a match
	for (int i = 0; i < playerNames.size(); i++)
	{
		if (playername == playerNames[i])
			return true;
	}
	// Return false if no player with that name exists
	return false;
}

//! Processes an array of player locations
void NetworkManager::ProcessArrayOfPlayerLocations(std::string updateMessage, Level& level, AgentManager& agentManager)
{
	std::string temp = "                                                                                                                                     ";
	//Create a list of all the players in the update message
	std::vector<std::string> allPlayers;
	int iterator = 0;
	// if the update message is not null
	if (updateMessage != "NULL" && updateMessage != "QUIT")
	{

		//TODO: get string of data between { and }
		for (int i = 0; i < updateMessage.size(); i++)
		{

			if (updateMessage[i] == *"{")
			{
				int dataSize = 0;
				for (int j = i; j < updateMessage.size(); j++)
				{
					if (updateMessage[j] == *"}")
						break;
					else
						dataSize++;
				}
				//Fill string with the data
				std::string playerData = "                                                                                                ";
				int t = 1;
				for (int d = i; d < i + dataSize; d++)
				{
					playerData[t] = updateMessage[d];
					t++;
				}
				playerData.erase(std::remove(playerData.begin(), playerData.end(), ' '), playerData.end());
				ProcessPlayerLocations(playerData, level, agentManager);
				iterator++;
			}
		}
		std::cout << "Number Of Players: " << iterator << std::endl;
	}

}
//! loops through the playerdata string and puts that into the agent manager
void NetworkManager::ProcessPlayerLocations(std::string updateMessage, Level& level, AgentManager& agentManager)
{
	if (updateMessage != "NULL" && updateMessage != "QUIT")
	{
		//print to console what the message is for debug purposes
		std::cout << "RECIEVE MESSAGE: " << updateMessage << std::endl;
		// Create a temp playername string to be overwirtten later
		std::string otherPlayerName = "                                                          ";

		// loop throuh the message to get the player name
		for (int i = 2; i < updateMessage.size(); i++)
		{
			if (updateMessage[i] != *">" && updateMessage[i + 1] != *" " && updateMessage[1] == *"<")
				otherPlayerName[i] = updateMessage[i];
			else
				break;
		}
		// Remove any spaces from name
		otherPlayerName.erase(std::remove(otherPlayerName.begin(), otherPlayerName.end(), ' '), otherPlayerName.end());


		// If the player already exists
		if (DoesPlayerExist(otherPlayerNames, otherPlayerName))
		{
			// If it does
			// Update Player Positions
			for (int i = 0; i < updateMessage.size(); i++)
			{
				// Don't go out of range
				if (i + 4 < updateMessage.size())
				{
					// Process X position
					if (updateMessage[i] == *"X" && updateMessage[i + 1] == *":")
					{
						// Convert string to int
						std::string::size_type sz;
						std::string updatenumber = "        ";
						if (updateMessage[i] + 5 != *"." || updateMessage[i] + 5 != *"Y")
							updatenumber[3] = updateMessage[i + 5];
						// Get the three digits after
						updatenumber[0] = updateMessage[i + 2]; updatenumber[1] = updateMessage[i + 3]; updatenumber[2] = updateMessage[i + 4];
						// Remove white space
						updatenumber.erase(std::remove(updatenumber.begin(), updatenumber.end(), ' '), updatenumber.end());
						//convert string to int
						int pos = std::stoi(updatenumber, &sz);
						//pos *= level.getCellSize();
						agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].setX(pos);

					}
					//Process Y position
					if (updateMessage[i] == *"Y" && updateMessage[i + 1] == *":")
					{

						// Convert string to int
						std::string::size_type sz;
						std::string updatenumber = "            ";
						if (updateMessage[i] + 5 != *"." || updateMessage[i] + 5 != *"A")
							updatenumber[3] = updateMessage[i + 5];
						// Get the three digits after
						updatenumber[0] = updateMessage[i + 2]; updatenumber[1] = updateMessage[i + 3]; updatenumber[2] = updateMessage[i + 4];
						// Remove white space
						updatenumber.erase(std::remove(updatenumber.begin(), updatenumber.end(), ' '), updatenumber.end());
						//convert string to int
						int pos = std::stoi(updatenumber, &sz);
						//pos *= level.getCellSize();
						agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].setY(pos);
					}



					// Update Player Actions
					std::string otherPlayerAction = "                                                                     ";
					if (updateMessage[i] == *"A" && updateMessage[i + 1] == *"C" && updateMessage[i + 2] == *"T" && updateMessage[i + 3] == *":")
					{
						for (int j = 0; j < 10; j++)
						{
							if (updateMessage[i + 4 + j] == *".")
								break;
							otherPlayerAction[j] = updateMessage[i + 4 + j];

						}
						//Remove Spaces
						otherPlayerAction.erase(std::remove(otherPlayerAction.begin(), otherPlayerAction.end(), ' '), otherPlayerAction.end());
						//Place bed on cell if the player places a bed
						if (otherPlayerAction == "PLACE_BED")
						{
							std::cout << otherPlayerAction << std::endl;
							level.grid[agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getX() / 50][agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getY() / 50]->isBed = true;
						}
						else if (otherPlayerAction == "PLACE_BOX")
						{
							std::cout << otherPlayerAction << std::endl;
							level.grid[agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getX() / 50][agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getY() / 50]->isCargo = true;
						}
					}
				}
			}
		}

		//Spawn new player
		else
		{
			if (otherPlayerName.size() > 1 && otherPlayerName != localPlayerName)
			{
				otherPlayerNames.push_back(otherPlayerName);
				Agent newPlayer;
				// If the agent is first player

				newPlayer.characterType = "NPC";
				newPlayer.agentCanRotate = true;

				newPlayer.setID(otherPlayerName);
				agentManager.SpawnAgent(newPlayer);
			}
		}

	}
}





//! sends a tcp message to the socket
void NetworkManager::sendTCPMessage(std::string message)
{
	// Fill the buffer with the data from the string
	boost::array<char, 128> buf;
	for (int i = 0; i < message.size(); i++)
	{
		buf[i] = message[i];
	}
	//Try sending the data
	try
	{
		boost::system::error_code error;
		socket->write_some(boost::asio::buffer(buf, message.size()), error);
		//std::cout << "Message sent: " << message << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}


//! returns a string from the socket
std::string NetworkManager::RecieveMessage()
{
	std::cout << "Recieveing message.." <<  std::endl;
	//Create return messages and an instream to put the buffer data into
	std::string returnMessage;
	std::stringstream inStream;
	try
	{
		boost::array<char, 128> buffer;
		boost::system::error_code error;

		// Read the data from the socket
		size_t len = socket->read_some(boost::asio::buffer(buffer), error);
		if (error == boost::asio::error::eof)
			return "QUIT"; // Connection closed cleanly by peer.
		else if (error)
			throw boost::system::system_error(error); // Some other error.

		//Print receive message
		//std::cout.write(buffer.data(), len);
		// Feed the buffer data into the inStream
		inStream << (buffer.data());

		// Convert inStream to string
		returnMessage = inStream.str();
		// Remove weird character that gets stuck the the end of messages
		returnMessage.erase(std::remove(returnMessage.begin(), returnMessage.end(), 'Ì'), returnMessage.end());

		// Return String
		return returnMessage;

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

}