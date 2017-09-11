#pragma once
#include "Level.h"
#include "AgentManager.h"
#include "Agent.h"
#include "Camera.h"
#include "NetworkManager.h"
#include "Player.h"
#include "ToolBar.h"
#include "InventoryUI.h"
class UserInput
{
public:
	UserInput();
	~UserInput();
	void UserInput::UseItemFromToolbar(ToolBar& toolbar, Player& player, Level& level, NetworkManager& networkManager, GameSettings& gameSettings);

	void UserInput::HandleUserInput(Level& level, Player& player, AgentManager& agentManager, NetworkManager& networkManager, Camera& camera, GameSettings& gameSettings, ToolBar& toolbar);

	bool UserInput::CheckIfCellIsWalkable(Level& level, int x, int y);

	void ChangeCellsAroundPoint(Level& level, glm::vec2 point, int dist, std::string type);
private:
	
	glm::vec2 playerChunkPos;
	glm::vec2 playercellPos;
	glm::vec2 InterDir;
};

