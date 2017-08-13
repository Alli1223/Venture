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
	io_service.run();
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

//! main netwrok update function
void NetworkManager::NetworkUpdate(Level& level, Player& player, AgentManager& agentManager)
{

	// Interval Timer
	timebehindP += SDL_GetTicks() - lastTimeP;
	lastTimeP = SDL_GetTicks();

	// Interval Timer
	timebehindM += SDL_GetTicks() - lastTimeM;
	lastTimeM = SDL_GetTicks();

	// Update intervalTimer
	while (timebehindP >= networkPlayerUpdateInterval)
	{
		runPlayerNetworkTick = true;
		timebehindP -= networkPlayerUpdateInterval;
	}
	while (timebehindM >= networkMapUpdateInterval)
	{
		runMapNetworkTick = true;
		timebehindM -= networkMapUpdateInterval;
	}

	// Update network
	if (runPlayerNetworkTick)
	{
		runPlayerNetworkTick = false;
		ProcessPlayerLocations(level, agentManager, player);
	}
	if (runMapNetworkTick)
	{
		runMapNetworkTick = false;
		//Process the map data
		MapNetworkUpdate(level);
	}
}

void NetworkManager::ProcessPlayerLocations(Level& level, AgentManager& agentManager, Player& player)
{
	//Create the json to send to the server
	json playerData;
	playerData["name"] = localPlayerName;
	playerData["rotation"] = player.getRotation();
	playerData["X"] = player.getX();
	playerData["Y"] = player.getY();


	sendTCPMessage("[PlayerUpdate]" + playerData.dump() + "\n");


	// process the list of players
	std::string updateData = RecieveMessage();

	// Remove anything at the end of the json string that isn't suppose to be there
	int endOfJsonString = updateData.find_last_of("}");
	int startOfJsonString = updateData.find_first_of("{");
	if(startOfJsonString >= 0)
	updateData.erase(updateData.begin(), updateData.begin() + startOfJsonString);
	if(endOfJsonString >= 0)
	updateData.erase(updateData.begin() + endOfJsonString + 1, updateData.end());

	try 
	{
		json jsonData = json::parse(updateData.begin(), updateData.end());;
		json playerData = jsonData.at("PlayerData");



		// range-based for
		for (auto& element : playerData)
		{
			int x = element.at("X").get<int>();
			int y = element.at("Y").get<int>();
			int rotation = element.at("rotation").get<int>();
			std::string name = element.at("name").get<std::string>();


			if (DoesPlayerExist(otherPlayerNames, name))
			{
				agentManager.allAgents[agentManager.GetAgentNumberFomID(name)].setX(x);
				agentManager.allAgents[agentManager.GetAgentNumberFomID(name)].setY(y);
				agentManager.allAgents[agentManager.GetAgentNumberFomID(name)].setTargetRotation(rotation);
			}
			else
			{
				if (name.size() > 1 && name != localPlayerName)
				{
					otherPlayerNames.push_back(name);
					Agent newPlayer;
					newPlayer.characterType = "NPC";
					newPlayer.setID(name);
					agentManager.SpawnAgent(newPlayer);
				}
			}
		}
	}
	catch (std::exception e)
	{
		std::cout << "Error processing player location data: " << e.what() << std::endl;
	}
}




//TODO: reimplement multi threaded networking
void NetworkManager::runMultiThread(std::shared_ptr<tcp::socket> socket, boost::asio::io_service& io_service)
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




//! Process map network update
//TODO: Don't create new cells on top, only replace the old ones
void NetworkManager::MapNetworkUpdate(Level& level)
{
	sendTCPMessage("[RequestMapUpdate]\n");
	std::string EmptyMap = "{\"MapData\":[]}\r\n";
	std::string mapData = RecieveMessage();
	if (mapData != EmptyMap)
	{
		// Remove anything at the end of the json string that isn't suppose to be there

		int endOfJsonString = mapData.find_last_of("}");
		int startOfJsonString = mapData.find_first_of("{");
		if (startOfJsonString >= 0)
			mapData.erase(mapData.begin(), mapData.begin() + startOfJsonString);
		int cellsUpdated = 0;

		try
		{
			json jsonData = json::parse(mapData.begin(), mapData.end());;
			json mapData = jsonData.at("MapData");

			// Range-based for loop to iterate through the map data
			for (auto& element : mapData)
			{
				int x = element.at("X").get<int>();
				int y = element.at("Y").get<int>();
				bool isFence = element.at("Fence").get<bool>();
				bool isDirt = element.at("Dirt").get<bool>();

				// Create a new cell to replace the old one
				Cell nc;
				nc.setPos(x, y);
				nc.isWoodFence = isFence;
				nc.isDirt = isDirt;
				level.SetCell(x, y, nc);
				cellsUpdated++;
			}
			std::cout << "Cells Updated: " << cellsUpdated << std::endl;
		}
		catch (std::exception e)
		{
			std::cout << "Error processing player location data: " << e.what() << std::endl;
		}
	}
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
							//level.tiles[agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getX() / 50][agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getY() / 50]->isBed = true;
						}
						else if (otherPlayerAction == "PLACE_BOX")
						{
							std::cout << otherPlayerAction << std::endl;
							//level.tiles[agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getX() / 50][agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getY() / 50]->isCargo = true;
						}
					}
				}
			}
		}

		// Spawn new player
		else
		{
			if (otherPlayerName.size() > 1 && otherPlayerName != localPlayerName)
			{
				otherPlayerNames.push_back(otherPlayerName);
				Agent newPlayer;
				newPlayer.characterType = "NPC";
				newPlayer.setID(otherPlayerName);
				agentManager.SpawnAgent(newPlayer);
			}
		}

	}
}





//! Sends a tcp message to the socket
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

std::string make_string(boost::asio::streambuf& streambuf)
{
	return { boost::asio::buffers_begin(streambuf.data()),
		boost::asio::buffers_end(streambuf.data()) };
}
//! returns a string from the socket
std::string NetworkManager::RecieveMessage()
{
	//Create return messages and an instream to put the buffer data into
	std::string returnMessage;
	std::stringstream inStream;
	try
	{
		boost::array<char, 128> buffer;
		boost::asio::streambuf read_buffer;
		 //bytes_transferred = boost::asio::write(*socket, write_buffer);
		 auto bytes_transferred = boost::asio::read_until(*socket, read_buffer, ("\r\n"));
		
		//std::cout << "Read: " << make_string(read_buffer) << std::endl;

		return returnMessage = make_string(read_buffer);

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
