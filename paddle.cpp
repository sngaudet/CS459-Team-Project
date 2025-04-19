#include <gl/glut.h>

class Paddle
{
	struct Rect
	{
		float x, y, z;
		float width, height, depth;
	};

	public:
		Rect rect;

		Paddle(float x, float y, float z, float width, float height, float depth)
		{
			rect.x = x;
			rect.y = y;
			rect.z = z;

			rect.width = width;
			rect.height = height;
			rect.depth = depth;
		}

		void drawPaddle()
		{
			glBegin(GL_QUADS);
				// top
				glVertex3f(rect.x - rect.width / 2, rect.y + rect.height / 2, rect.z - rect.depth / 2);
				glVertex3f(rect.x - rect.width / 2, rect.y + rect.height / 2, rect.z + rect.depth / 2);
				glVertex3f(rect.x + rect.width / 2, rect.y + rect.height / 2, rect.z + rect.depth / 2);
				glVertex3f(rect.x + rect.width / 2, rect.y + rect.height / 2, rect.z - rect.depth / 2);
				// bottom
				glVertex3f(rect.x - rect.width / 2, rect.y - rect.height / 2, rect.z - rect.depth / 2);
				glVertex3f(rect.x - rect.width / 2, rect.y - rect.height / 2, rect.z + rect.depth / 2);
				glVertex3f(rect.x + rect.width / 2, rect.y - rect.height / 2, rect.z + rect.depth / 2);
				glVertex3f(rect.x + rect.width / 2, rect.y - rect.height / 2, rect.z - rect.depth / 2);
			glEnd();
		}

};