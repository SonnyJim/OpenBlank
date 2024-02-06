enum GameState
{
	STATE_GAMEOVER,
	STATE_ROUND_START,
	STATE_ROUND_ACTIVE,
	STATE_ROUND_END,
};

class Game
{
	public:
		void start();
		void end();
		void update();
		GameState getState();
		void setState(GameState s);
	private:
		GameState state;
		int round; //Which round are we on
};
