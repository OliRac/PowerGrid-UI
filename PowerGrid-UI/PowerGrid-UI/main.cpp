#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/OpenGL.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <thread>
#include <iostream>
#include <string>
#include <vector>

#include "Game.h"
#include "Action.h"
#include "Stats.h"

using std::cout;
using std::endl;
using std::to_string;
using std::thread;
using std::string;
using std::vector;

/*Unfortunately, I've had to hide all references to the actual game we were programming. 95% of the code is not here. This is purely to spread the joy of ImGUI.*/
void playGame(Action * ac, Stats * stat, Game * game) {
	game->play();
	cout << "Game execution is over! Please close the UI window in order to exit the application properly." << endl;
}

void showGUI(Action * ac, Stats * stat) {
	sf::RenderWindow window(sf::VideoMode(600, 600), "Power Grid UI");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);


	window.resetGLStates();
	sf::Clock deltaClock;


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		//note: use .c_str() to make char arrays for imgui

		ImGui::SFML::Update(window, deltaClock.restart());

		sf::Color bgcolor(115, 150, 163);


		/**********Action Window**********/
		ImGui::Begin("Action Output");

		string phase = ac->getPhaseMsg();
		string action = "Action: " + ac->getActionMsg();
		string player = "Player: " + to_string(ac->getPlayerID());

		ImGui::Text(phase.c_str());
		ImGui::Text(action.c_str());

		if (ac->getPlayerID() != 0) {
			ImGui::Text(player.c_str());
		}

		ImGui::End();


		/**********Stats Window**********/
		ImGui::Begin("Game Stats Output");

			/*
				Menu that presents information for each player in the game
					Player start region
					Player locations
					Player cash
					Player castles
					Player resources

				Graphs:
					cash per player
					shop contents
			*/
			if (ImGui::CollapsingHeader("Player Information")) {
				for (int i = 0; i < stat->getNumPlayers(); i++) {

					/*Player id*/
					ImGui::Text(("Player " + to_string(i)).c_str());


					/*Start region*/
					ImGui::Text(("Starting region: " + stat->getStartRegions()[i]).c_str());


					/*Locations*/
					string locationStr = "Cities built in: ";

					vector<string> names = stat->getLocations()[i];

					for (string str : names) {
						locationStr.append(str + ", ");
					}

					ImGui::Text(locationStr.c_str());


					/*Elektros*/
					ImGui::Text(("Cash: " + to_string((stat->getCash())[i])).c_str());


					/*Castles*/
					string castleStr = "Castles owned: ";

					vector<int> castlesVec = stat->getCastles()[i];

					for (int plant : castlesVec) {
						castleStr += "#" + to_string(plant) + " ";
					}

					ImGui::Text(castleStr.c_str());

					/*
						Resources
						0 = copper
						1 = iron
						2 = gold
						3 = mithril
					*/
					string resStr = "Resources: ";
					resStr += to_string(stat->getResources()[i][0]) + " copper, ";
					resStr += to_string(stat->getResources()[i][1]) + " iron, ";
					resStr += to_string(stat->getResources()[i][2]) + " gold, ";
					resStr += to_string(stat->getResources()[i][3]) + " mithril";

					ImGui::Text(resStr.c_str());

					ImGui::Separator();
				}
			}

			/*Menu that presents a histogram of cash per player*/
			if (ImGui::CollapsingHeader("Bar Graphs")) {

				/*Cash per player...ImGui needs floats*/
				vector<float> cashFl;

				int max = 0;

				for (int i : stat->getCash()) {
					cashFl.push_back(static_cast<float>(i));

					if (max < i) {
						max = i;
					}
				}

				ImGui::PlotHistogram("##elekValues", &cashFl[0], cashFl.size(), 0, "Cash per player", 0.0f, (static_cast<float>(max) * 1.5), ImVec2((ImGui::GetWindowWidth() - 15), 200));

				ImGui::Separator();
				ImGui::Separator();
				ImGui::Separator();

				/*Resources in the shop*/
				vector<float> resourceFlVal;

				for (int i : stat->getShop()) {
					resourceFlVal.push_back(static_cast<float>(i));
				}

				ImGui::PlotHistogram("##resValues", &resourceFlVal[0], resourceFlVal.size(), 0, "Shop contents", 0.0f, 28.0f, ImVec2((ImGui::GetWindowWidth() - 15), 200));

				ImGui::Text("0 = copper, 1 = iron, 2 = gold, 3 = mithril");
			}

			/*Map connections*/
			/*Doing a big table where all the powerlines are represented*/
			if (ImGui::CollapsingHeader("Connections")) {
				ImGui::Columns(3, "Connections");
				ImGui::SetColumnWidth(0, 175);
				ImGui::SetColumnWidth(1, 175);
				ImGui::SetColumnWidth(2, 150);
				ImGui::Text("Source");
				ImGui::NextColumn();
				ImGui::Text("Target");
				ImGui::NextColumn();
				ImGui::Text("Cost");
				ImGui::Separator();
				ImGui::NextColumn();

				for (auto conn : stat->getConnections()) {
					ImGui::AlignTextToFramePadding();
					ImGui::Text(conn.getSource().c_str());
					ImGui::NextColumn();

					ImGui::AlignTextToFramePadding();
					ImGui::Text(conn.getTarget().c_str());
					ImGui::NextColumn();

					ImGui::AlignTextToFramePadding();
					ImGui::Text((to_string(conn.getCost())).c_str());
					ImGui::Separator();

					ImGui::NextColumn();
				}
			}

		ImGui::End();

		window.clear(bgcolor);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}

int main() {
	Game * game = new Game();
	Action * ac = new Action();
	Stats * stat = new Stats();

	//launch threads
	thread gameThread(playGame, ac, stat, game);
	thread guiThread(showGUI, ac, stat);

	gameThread.join();
	guiThread.join();

	delete game;
	delete ac;
	delete stat;

	return 0;
}