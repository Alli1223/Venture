#include "stdafx.h"
#include "UserInput.h"


UserInput::UserInput()
{
}


UserInput::~UserInput()
{
}

void UserInput::HandleUserInput(Level& level, AgentManager& agentManager, NetworkManager& networkManager, Camera& camera, std::string playerName, bool useNetworking, bool& running)
{
	int cellSize = level.getCellSize();
	SDL_Event ev;
	if (SDL_PollEvent(&ev))
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE])
			running = false;

		// Player Movement
		if (state[SDL_SCANCODE_S])
		{
			if (agentManager.allAgents.size() > 0)
				agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].agentRotation = 0;
			agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].setY(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getY() + agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed());
		}
		if (state[SDL_SCANCODE_A])
		{
			if (agentManager.allAgents.size() > 0)
				agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].agentRotation = 90;
			agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].setX(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getX() - agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed());

		}
		if (state[SDL_SCANCODE_D])
		{
			if (agentManager.allAgents.size() > 0)
				agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].agentRotation = 270;
			agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].setX(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getX() + agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed());
		}
		if (state[SDL_SCANCODE_W])
		{
			if (agentManager.allAgents.size() > 0)
				agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].agentRotation = 180;
			agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].setY(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getY() - agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed());
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//CAMERA
		//Set offset to camera
		if (state[SDL_SCANCODE_RIGHT])
			camera.SetPos(camera.getX() + camera.getCameraSpeed(), camera.getY());

		if (state[SDL_SCANCODE_DOWN])
			camera.SetPos(camera.getX(), camera.getY() + camera.getCameraSpeed());

		if (state[SDL_SCANCODE_LEFT])
			camera.SetPos(camera.getX() - camera.getCameraSpeed(), camera.getY());

		if (state[SDL_SCANCODE_UP])
			camera.SetPos(camera.getX(), camera.getY() - camera.getCameraSpeed());


		if (state[SDL_SCANCODE_PAGEUP])
			level.setCellSize(level.getCellSize() + 1);
		if (state[SDL_SCANCODE_PAGEDOWN] && level.getCellSize() > 0)
			level.setCellSize(level.getCellSize() - 1);

		if (state[SDL_SCANCODE_SPACE])
		{

		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Player Actions
		else if (state[SDL_SCANCODE_B])
			networkManager.sendTCPMessage("PLACE_BED\n");
		else if (state[SDL_SCANCODE_C])
			networkManager.sendTCPMessage("PLACE_BOX\n");
	}

}