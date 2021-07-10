#include "GUI.h"
#include "Window.h"
#include <chrono>
constexpr auto M_PI = 3.14159265358979323846;
using namespace Graph_lib;
using namespace std::chrono;

struct Analog_window : Graph_lib::Window
{
	Analog_window(Point xy, int w, int h, const string& title):
		Window(xy, w, h, title),
		radius(w > h ? h / 2 : w / 2),
		center(w / 2, h / 2),
		circle(center, radius)
	{
		Vector_ref<Text> ts;
		Vector_ref<Line> ls;
		for (int i = 0; i < 60; i++)
		{
			ls.push_back(new Line(point_of_circle(rad(i * 6), radius), point_of_circle(rad(i * 6), radius - 20)));
			ls[i].set_color(Color::black);
			attach(ls[i]);
		}
		for (int i = 1; i <= 12; i++)
		{
			ts.push_back(new Text(point_of_circle(rad(180 - i * 30), radius - 50), std::to_string(i)));
			ts[i - 1].set_font_size(24);
			ts[i - 1].set_color(Color::black);
			attach(ts[i - 1]);
		}
		circle.set_color(Color::black);
		attach(circle);
		process();
	}

private:
	void process()
	{
		while (true)
		{
			stringstream ss;
			ss.str(currentDateTime());
			double hour, minute, second;
			char ch1, ch2;
			ss >> hour >> ch1 >> minute >> ch2 >> second;
			hour += minute / 60;
			hour += second / 3600;
			minute += second / 60;
			Line lhour(center, point_of_circle(rad(180 - hour * 30), radius / 2));
			Line lminute(center, point_of_circle(rad(180 - minute * 6), radius / 3 * 2));
			Line lsecond(center, point_of_circle(rad(180 - second * 6), radius));
			lhour.set_color(Color::red);
			lminute.set_color(Color::blue);
			lsecond.set_color(Color::black);
			attach(lhour);
			attach(lminute);
			attach(lsecond);
			Fl::wait(1);
			Fl::redraw();
		}
	}

	int radius;
	Point center;

	static double rad(double angle)
	{
		return (angle * M_PI / 180);
	}

	Point point_of_circle(double rad, int r) const
	{
		return Point(center.x + (r * sin(rad)), center.y + (r * cos(rad)));
	}

	static std::string currentDateTime()
	{
		time_t now = time(nullptr);
		struct tm tstruct;
		char buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%X", &tstruct);

		return buf;
	}

	// Line lhour, lminute, lsecond;
	Circle circle;
};


int main()
{
	Analog_window window(Point(200, 100), 900, 900, "Analog Clock");
	return gui_main();
}
