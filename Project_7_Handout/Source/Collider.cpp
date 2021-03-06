#include "Collider.h"

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener): rect(rectangle), type(type)
{
	listeners[0] = listener;
}

Collider::Collider(SDL_Rect rectangle, Type type, Enemy* listener){

	listenersE[0] = listener;

}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
void Collider::SetPos(fPoint floatPoint)
{
	rect.x = floatPoint.x;
	rect.y = floatPoint.y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}

void Collider::AddListener(Module* listener)
{
	for (int i = 0; i < MAX_LISTENERS; ++i)
	{
		if (listeners[i] == nullptr)
		{
			listeners[i] = listener;
			break;
		}

		//Simple security check to avoid adding the same listener twice
		else if (listeners[i] == listener)
			break;
	}
}

void Collider::AddListener(Enemy* listener)
{
	for (int i = 0; i < MAX_LISTENERS; ++i)	{
		if (listenersE[i] == nullptr)		{
			listenersE[i] = listener;
			break;
		}

		//Simple security check to avoid adding the same listener twice
		else if (listenersE[i] == listener)
			break;
	}
}