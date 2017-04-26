#ifndef __PAUSESTATE__
#define __PAUSESTATE__

#include <vector>

class Gameobject;

class PauseState : public GameState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const {return m_pauseID;}

private:

	static void s_pauseToMain();
	static void s_resumePlay();

	static const std::string s_pauseID;

	std::vector<Gameobject*> m_gameObjects;
};

#endif