#include <iostream>
#include <vector>

#include <ctime>

void output(const std::vector<size_t>& v_, const size_t x_, const size_t y_) {
	for (size_t i = 0; i < y_; ++i) {
		for (size_t j = 0; j < x_; ++j) {
			switch (v_[i*x_ + j])
			{
				//case 0:std::cout << "¡";break;
			case 0:std::cout << " "; break;
				//case 0:std::cout << "‚O"; break;
			case 1:std::cout << "‚P"; break;
			case 2:std::cout << "‚Q"; break;
			case 3:std::cout << "‚R"; break;
			case 4:std::cout << "‚S"; break;
			case 5:std::cout << "‚T"; break;
			case 6:std::cout << "‚U"; break;
			case 7:std::cout << "‚V"; break;
			case 8:std::cout << "‚W"; break;
			case 9:std::cout << "‚X"; break;
			case 10:std::cout << "‚ "; break;
			case 11:std::cout << "‚‚"; break;
			case 12:std::cout << "‚ƒ"; break;
			case 13:std::cout << "‚„"; break;
			case 14:std::cout << "‚¦"; break;
			case 15:std::cout << "‚†"; break;
			case 16:std::cout << "‚‡"; break;
			case 17:std::cout << "‚ˆ"; break;
			case 18:std::cout << "‚¢"; break;
			case 19:std::cout << "‚Š"; break;
			}
		}
		std::cout << std::endl;
	}
}

struct roguelike {
	//•ªŠ„ƒ}ƒbƒv‚Ì”ÍˆÍˆÊ’u
	size_t dx1{};
	size_t dy1{};
	size_t dx2{};
	size_t dy2{};

	//•”‰®ƒ}ƒbƒv‚Ì”ÍˆÍˆÊ’u
	size_t rx1{};
	size_t ry1{};
	size_t rx2{};
	size_t ry2{};
};

struct roguelikeAll {
private:
	size_t num;
public:
	std::unique_ptr<roguelike[]> rl;
	std::unique_ptr<std::vector<size_t>[]> rv;
	const size_t size() const { return num; }
	void reset(const size_t num_) { rl.reset(new roguelike[num_]); rv.reset(new std::vector<size_t>[num_]); }
	roguelikeAll(const size_t num_) :num(num_) { this->reset(num_); }
};

void division(const size_t x_, const size_t y_, const roguelikeAll& rla_) {
	if (rla_.size() == 0 || x_ == 0 || y_ == 0) return;
	rla_.rl[0].dx1 = 0;
	rla_.rl[0].dy1 = 0;
	rla_.rl[0].dx2 = x_;
	rla_.rl[0].dy2 = y_;

	size_t div_num = 0;
	size_t xy_num = 0;
	size_t rand_length = 0;

	for (size_t i = 1; i < rla_.size(); ++i) {
		div_num = (rand() % i);

		if ((rla_.rl[div_num].dx2 - rla_.rl[div_num].dx1) > (rla_.rl[div_num].dy2 - rla_.rl[div_num].dy1)) xy_num = 0;
		else xy_num = 1;
		//xy_num = (rand() & 1);

		switch (xy_num)
		{
		case 0:
			rand_length = (rla_.rl[div_num].dx2 - rla_.rl[div_num].dx1) / 2;
			rla_.rl[i].dx2 = rla_.rl[div_num].dx2;
			rla_.rl[i].dy1 = rla_.rl[div_num].dy1;
			rla_.rl[i].dy2 = rla_.rl[div_num].dy2;

			if (rand_length == 0) {
				rla_.rl[i].dx1 = rla_.rl[div_num].dx1;
				break;
			}
			rla_.rl[div_num].dx2 = rla_.rl[div_num].dx1 + (rand() % rand_length) + rand_length / 2;
			rla_.rl[i].dx1 = rla_.rl[div_num].dx2;
			break;
		case 1:
			rand_length = (rla_.rl[div_num].dy2 - rla_.rl[div_num].dy1) / 2;
			rla_.rl[i].dy2 = rla_.rl[div_num].dy2;
			rla_.rl[i].dx1 = rla_.rl[div_num].dx1;
			rla_.rl[i].dx2 = rla_.rl[div_num].dx2;

			if (rand_length == 0) {
				rla_.rl[i].dy1 = rla_.rl[div_num].dy1;
				break;
			}
			rla_.rl[div_num].dy2 = rla_.rl[div_num].dy1 + (rand() % rand_length) + rand_length / 2;
			rla_.rl[i].dy1 = rla_.rl[div_num].dy2;
			break;
		}
	}
	return;
}

void room(const size_t x_, const size_t y_, const roguelikeAll& rla_) {
	size_t rand_length_x = 0;
	size_t rand_length_y = 0;
	for (size_t i = 0; i < rla_.size(); ++i) {
		rand_length_x = (rla_.rl[i].dx2 - rla_.rl[i].dx1) / 4;
		rand_length_y = (rla_.rl[i].dy2 - rla_.rl[i].dy1) / 4;
		rla_.rl[i].rx1 = rla_.rl[i].dx1 + rand_length_x;
		rla_.rl[i].rx2 = rla_.rl[i].dx2 - rand_length_x;
		rla_.rl[i].ry1 = rla_.rl[i].dy1 + rand_length_y;
		rla_.rl[i].ry2 = rla_.rl[i].dy2 - rand_length_y;
	}
}

void divisionOutput(std::vector<size_t>& v_, const size_t x_, const roguelikeAll& rla_) {
	for (size_t k = 0; k < rla_.size(); ++k)
		for (size_t i = rla_.rl[k].dy1; i < rla_.rl[k].dy2; ++i)
			for (size_t j = rla_.rl[k].dx1; j < rla_.rl[k].dx2; ++j)
				v_[i*x_ + j] = k + 1;
}
void roomOutput(std::vector<size_t>& v_, const size_t x_, const roguelikeAll& rla_) {
	for (size_t k = 0; k < rla_.size(); ++k)
		for (size_t i = rla_.rl[k].ry1; i < rla_.rl[k].ry2; ++i)
			for (size_t j = rla_.rl[k].rx1; j < rla_.rl[k].rx2; ++j)
				v_[i*x_ + j] = 0;
}

void next(const roguelikeAll& rla_) {
	bool is = false;
	for (size_t i = 0; i < rla_.size(); ++i) {
		for (size_t j = i; j < rla_.size(); ++j) {
			is = false;
			if (rla_.rl[i].dy1 == rla_.rl[j].dy2 || rla_.rl[i].dy2 == rla_.rl[j].dy1) {
				if (rla_.rl[i].dx1 <= rla_.rl[j].dx1&&rla_.rl[i].dx2 > rla_.rl[j].dx1) is = true;
				else if (rla_.rl[i].dx1 < rla_.rl[j].dx2&&rla_.rl[i].dx2 >= rla_.rl[j].dx2) is = true;
			}
			else if (rla_.rl[i].dx1 == rla_.rl[j].dx2 || rla_.rl[i].dx2 == rla_.rl[j].dx1) {
				if (rla_.rl[i].dy1 <= rla_.rl[j].dy1&&rla_.rl[i].dy2 > rla_.rl[j].dy1) is = true;
				else if (rla_.rl[i].dy1 < rla_.rl[j].dy2&&rla_.rl[i].dy2 >= rla_.rl[j].dy2) is = true;
			}
			if (is) {
				rla_.rv[i].emplace_back(j);
				rla_.rv[j].emplace_back(i);
			}
		}
	}
}

void nextOutput(const roguelikeAll& rla_) {
	for (size_t k = 0; k < rla_.size(); ++k) {
		std::cout << (k + 1) << ':';
		for (size_t i = 0; i < rla_.rv[k].size(); ++i) {
			std::cout << (rla_.rv[k][i] + 1) << ',';
		}
		std::cout << std::endl;
	}
}

int main() {

	srand((unsigned int)time(nullptr));

	constexpr size_t x = 40;
	constexpr size_t y = 30;
	std::vector<size_t> vint(x*y, 0);

	roguelikeAll rla(8);
	division(x, y, rla);
	divisionOutput(vint, x, rla);

	room(x, y, rla);
	roomOutput(vint, x, rla);

	output(vint, x, y);

	next(rla);
	nextOutput(rla);

	return 0;
}