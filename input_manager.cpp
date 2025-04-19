#include <gl/glut.h>

class InputManager
{
	struct Mouse
	{
		int prevMouseX;
		int prevMouseY;
		int mouseX;
		int mouseY;

		int mouseMotionX;
		int mouseMotionY;

		bool prevLeftPressed;
		bool leftPressed;
		bool prevRightPressed;
		bool rightPressed;
	};
	
public:
	Mouse m;

	void keyboard(unsigned char key, int x, int y)
	{

	}

	void specialKeyboard(int key, int x, int y)
	{

	}

	void mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			m.leftPressed = true;
		}
		else
		{
			m.leftPressed = false;
		}

		m.prevLeftPressed = m.leftPressed;
		m.prevRightPressed = m.rightPressed;
	}

	void mouseMotion(int x, int y)
	{
		m.mouseX = x;
		m.mouseY = y;

		m.mouseMotionX = m.prevMouseX - m.mouseX;
		m.mouseMotionY = m.prevMouseX - m.mouseY;

		m.prevMouseX = m.mouseX;
		m.prevMouseY = m.mouseY;
	}

	int* getMousePosition()
	{
		int mouseVector[2] = { m.mouseX, m.mouseY};
		return mouseVector;
	}
};