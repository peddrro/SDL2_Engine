#include "MainMenuState.h"
#include "TextureManager.h"
#include "game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"
#include <stdio.h>
using namespace std;

const string MainMenuState::s_menuID = "MENU";

void MainMenuState::update(){
	for(unsigned i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MainMenuState::render(){
	for(unsigned i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MainMenuState::onEnter(){
	// parse the state
	StateParser stateParser;
	stateParser.parseState("xml/test.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0); //pushback 0 callbackID start from 1
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);
	// set the callbacks for menu items
	setCallbacks(m_callbacks);

	printf("entering MainMenuState\n");
	return true;
}

bool MainMenuState::onExit(){
	for(unsigned i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	for(unsigned i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	printf("exiting MainMenuState\n");

	return true;
}

void MainMenuState::s_menuToPlay(){
	Game::Instance()->getStateMachine()->changeState(new PlayState());
	printf("Play button clicked\n");
}
void MainMenuState::s_exitFromMenu(){
	printf("Exit button clicked\n");
	Game::Instance()->quit();
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks){
// go through the game objects
	for(unsigned i = 0; i < m_gameObjects.size(); i++){
// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if(dynamic_cast<MenuButton*>(m_gameObjects[i])){
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}