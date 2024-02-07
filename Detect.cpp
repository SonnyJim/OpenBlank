#include "Player.h"
#include "LTarget.h"

static bool check_target (int target)
{
	if (gTargets[target].getType() == TARGET_NONE)
		return false;
	SDL_Rect rect = gTargets[target].getRect();
	SDL_Point point = players[0].getPosition();
	bool withinXBounds = point.x >= rect.x && point.x < (rect.x + rect.w);
	bool withinYBounds = point.y >= rect.y && point.y < (rect.y + rect.h);
	//fprintf (stdout, "x=%i, y=%i, w=%i, h=%i rect\n", rect.x, rect.y, rect.w, rect.h);
	//fprintf (stdout, "x=%i, y=%i Point x=%i, y=%i\n", point.x, point.y, withinXBounds, withinYBounds);
	return withinXBounds && withinYBounds;
}

bool detect_shot ()
{
	//fprintf (stdout, "Detecting shots\n");
	int i;
	for (i = 0; i < MAX_TARGETS; i++)
	{
	//	fprintf(stdout, "Check target %i\n", i);
		if (check_target(i) == true)
		{
			gTargets[i].hit();
			return true;
			//FIXME What if we hit two overlapping targets?
		}
	}
	
	return false;
}
