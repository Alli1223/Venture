#pragma once
#include "Level.h"
#include "AgentManager.h"
#include "Agent.h"
#include "Camera.h"
#include "NetworkManager.h"
class UserInput
{
public:
	UserInput();
	~UserInput();

	void UserInput::HandleUserInput(Level& level, AgentManager& agentManager, NetworkManager& networkManager, Camera& camera, std::string playerName, bool useNetworking, bool& running);

	bool UserInput::CheckIfCellIsWalkable(Level& level, int x, int y);
private:
	glm::vec2 playerChunkPos;
	glm::vec2 playercellPos;
	glm::vec2 InterDir;
};

