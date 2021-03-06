#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() : SDLGameObject(){
	
}

void MenuButton::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::setCallback(void(*callback)()){
	m_callback = callback;
}

int MenuButton::getCallbackID(){
	return m_callbackID;
}

void MenuButton::draw()
{
	SDLGameObject::draw(); // use the base class drawing
}
void MenuButton::update()
{
	Vector2D pMousePos = InputHandler::Instance()->getMousePosition();
	
	if(pMousePos.getX() < (m_position.getX() + m_width) 
		&& pMousePos.getX() > m_position.getX() 
		&& pMousePos.getY() < (m_position.getY() + m_height) 
		&& pMousePos.getY() > m_position.getY())
	{		
		m_currentFrame = MOUSE_OVER;
		if(InputHandler::Instance()->getMouseButtonState(LEFT) and m_bReleased){
			m_currentFrame = CLICKED;
			m_callback();
			m_bReleased = false;
		}
		else if(!InputHandler::Instance()->getMouseButtonState(LEFT)){
		m_bReleased = true;
		m_currentFrame = MOUSE_OVER;
		}
	}
	else{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean(){
	SDLGameObject::clean();
}