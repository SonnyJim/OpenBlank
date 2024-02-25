class Background
{
	public:
		void render ();
		void set (std::string path);
		void clear ();
	private:
		bool active;

};
extern Background bg;
