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
	if (SDL_PollEvent(&ev) != 0) {
		if (ev.type == SDL_QUIT) {
			running = false;
		}
	}
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
		running = false;

	int playerX = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getX();
	int playerY = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getY();
	int playerSpeed = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed();
	int agentNo = agentManager.GetAgentNumberFomID(playerName);


	//Diagonal movement
	if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D])
	{
		agentManager.allAgents[agentNo].targetRotation = 225;
		agentManager.allAgents[agentNo].setPosition(playerX + playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
	{
		agentManager.allAgents[agentNo].targetRotation = 135;
		agentManager.allAgents[agentNo].setPosition(playerX - playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])
	{
		agentManager.allAgents[agentNo].targetRotation = -45;
		agentManager.allAgents[agentNo].setPosition(playerX + playerSpeed, playerY + playerSpeed);

	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])
	{
		agentManager.allAgents[agentNo].targetRotation = 45;
		agentManager.allAgents[agentNo].setPosition(playerX - playerSpeed, playerY + playerSpeed);
	}
	// Player Movement
	else if (state[SDL_SCANCODE_S])
	{
		agentManager.allAgents[agentNo].targetRotation = 0;
		agentManager.allAgents[agentNo].setY(playerY + playerSpeed);
	}
	else if (state[SDL_SCANCODE_A])
	{
		agentManager.allAgents[agentNo].targetRotation = 90;
		agentManager.allAgents[agentNo].setX(playerX - playerSpeed);

	}
	else if (state[SDL_SCANCODE_D])
	{
		agentManager.allAgents[agentNo].targetRotation = 270;
		agentManager.allAgents[agentNo].setX(playerX + playerSpeed);
	}
	else if (state[SDL_SCANCODE_W])
	{
		agentManager.allAgents[agentNo].targetRotation = 180;
		agentManager.allAgents[agentNo].setY(playerY - playerSpeed);
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
	if (state[SDL_SCANCODE_PAGEDOWN] && level.getCellSize() > 1)
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

