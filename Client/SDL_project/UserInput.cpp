#include "stdafx.h"
#include "UserInput.h"


UserInput::UserInput()
{
}


UserInput::~UserInput()
{
}

void UserInput::HandleUserInput(Level& level, AgentManager& agentManager, NetworkManager& networkManager, Camera& camera, std::string playerName, bool useNetworking, bool running)
{
	int cellSize = level.getCellSize();
	SDL_Event ev;
	if (SDL_PollEvent(&ev))
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		switch (ev.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
		case SDL_SCANCODE_ESCAPE:
			running = false;
			break;
		case SDL_SCANCODE_S:
			if (agentManager.allAgents.size() > 0)
				agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].agentRotation = 0;
			if (useNetworking)
			{
				networkManager.sendTCPMessage("MOVE_SOUTH\n");
				networkManager.NetworkUpdate(level, agentManager);
			}
			else
				agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].setY(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getY() + agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed());



			// Player Movement
			if (state[SDL_SCANCODE_S])
			{
				if (agentManager.allAgents.size() > 0)
					agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].agentRotation = 0;
				if (useNetworking)
				{
					networkManager.sendTCPMessage("MOVE_SOUTH\n");
					networkManager.NetworkUpdate(level, agentManager);
				}
				else
					agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].setY(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getY() + agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed());

			}
			if (state[SDL_SCANCODE_A])
			{
				if (agentManager.allAgents.size() > 0)
					agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].agentRotation = 90;
				if (useNetworking)
				{
					networkManager.sendTCPMessage("MOVE_WEST\n");
					networkManager.NetworkUpdate(level, agentManager);
				}
				else
					agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].setX(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getX() - agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed());

			}
			if (state[SDL_SCANCODE_D])
			{
				if (agentManager.allAgents.size() > 0)
					agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].agentRotation = 270;
				if (useNetworking)
				{
					networkManager.sendTCPMessage("MOVE_EAST\n");
					networkManager.NetworkUpdate(level, agentManager);
				}
				else
					agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].setX(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getX() + agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed());

			}
			if (state[SDL_SCANCODE_W])
			{
				if (agentManager.allAgents.size() > 0)
					agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].agentRotation = 180;
				if (useNetworking)
				{
					networkManager.sendTCPMessage("MOVE_NORTH\n");
					networkManager.NetworkUpdate(level, agentManager);
				}
				else
					agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].setY(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getY() - agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed());
			}

			//Set offset to camera
			if (state[SDL_SCANCODE_RIGHT] && camera.getX() / cellSize < level.grid.size())
			{
				camera.xoffset++;
				for (int i = 0; i < agentManager.allAgents.size(); i++)
					agentManager.allAgents[i].setOffsetX(-camera.xoffset * cellSize);

			}
			if (state[SDL_SCANCODE_DOWN] && camera.yoffset < level.grid[0].size())
			{
				camera.yoffset++;
				for (int i = 0; i < agentManager.allAgents.size(); i++)
					agentManager.allAgents[i].setOffsetY(-camera.yoffset * cellSize);

			}
			if (state[SDL_SCANCODE_LEFT] && camera.xoffset > 0)
			{
				camera.xoffset--;
				for (int i = 0; i < agentManager.allAgents.size(); i++)
					agentManager.allAgents[i].setOffsetX(-camera.xoffset * cellSize);

			}
			if (state[SDL_SCANCODE_UP] && camera.yoffset > 0)
			{
				camera.yoffset--;
				for (int i = 0; i < agentManager.allAgents.size(); i++)
					agentManager.allAgents[i].setOffsetY(-camera.yoffset * cellSize);
			}
			if (state[SDL_SCANCODE_PAGEUP])
				level.setCellSize(level.getCellSize() + 1);
			if (state[SDL_SCANCODE_PAGEDOWN])
				level.setCellSize(level.getCellSize() - 1);

			// Player Actions
			else if (state[SDL_SCANCODE_B])
				networkManager.sendTCPMessage("PLACE_BED\n");
			else if (state[SDL_SCANCODE_C])
				networkManager.sendTCPMessage("PLACE_BOX\n");
		}
	}
}