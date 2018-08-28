#include <iostream>
#include <vector>

#include <ctime>

void output(const std::vector<size_t>& v_, const size_t x_, const size_t y_) {
	for (size_t i = 0; i < y_; ++i) {
		for (size_t j = 0; j < x_; ++j) {
			switch (v_[i*x_ + j])
			{
				//case 0:std::cout << "■";break;
			case 0:std::cout << "□"; break;
				//case 0:std::cout << "０"; break;
			case 1:std::cout << "１"; break;
			case 2:std::cout << "２"; break;
			case 3:std::cout << "３"; break;
			case 4:std::cout << "４"; break;
			case 5:std::cout << "５"; break;
			case 6:std::cout << "６"; break;
			case 7:std::cout << "７"; break;
			case 8:std::cout << "８"; break;
			case 9:std::cout << "９"; break;
			case 10:std::cout << "あ"; break;
			case 11:std::cout << "ｂ"; break;
			case 12:std::cout << "ｃ"; break;
			case 13:std::cout << "ｄ"; break;
			case 14:std::cout << "え"; break;
			case 15:std::cout << "ｆ"; break;
			case 16:std::cout << "ｇ"; break;
			case 17:std::cout << "ｈ"; break;
			case 18:std::cout << "い"; break;
			case 19:std::cout << "ｊ"; break;
			}
		}
		std::cout << std::endl;
	}
}

struct roguelike {
	//分割マップの範囲位置
	size_t dx1{};
	size_t dy1{};
	size_t dx2{};
	size_t dy2{};

	//部屋マップの範囲位置
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
	std::unique_ptr<std::vector<size_t>[]> rvid;
	const size_t size() const { return num; }
	void reset(const size_t num_) {
		rl.reset(new roguelike[num_]);
		rv.reset(new std::vector<size_t>[num_]);
		rvid.reset(new std::vector<size_t>[num_]);
	}
	void reset() {
		rl.reset();
		rv.reset();
		rvid.reset();
	}
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
	bool&& is_id = false;
	size_t id = 0;
	for (size_t i = 0; i < rla_.size(); ++i) {
		for (size_t j = i; j < rla_.size(); ++j) {
			is = false;
			if ((is_id=(rla_.rl[i].dy1 == rla_.rl[j].dy2)) || rla_.rl[i].dy2 == rla_.rl[j].dy1) {
				if(is_id) id = 1;
				else id = 0;
				if (rla_.rl[i].dx1 <= rla_.rl[j].dx1&&rla_.rl[i].dx2 > rla_.rl[j].dx1) is = true;
				else if (rla_.rl[i].dx1 < rla_.rl[j].dx2&&rla_.rl[i].dx2 >= rla_.rl[j].dx2) is = true;
			}
			else if ((is_id=(rla_.rl[i].dx1 == rla_.rl[j].dx2)) || rla_.rl[i].dx2 == rla_.rl[j].dx1) {
				if (is_id) id = 3;
				else id = 2;
				if (rla_.rl[i].dy1 <= rla_.rl[j].dy1&&rla_.rl[i].dy2 > rla_.rl[j].dy1) is = true;
				else if (rla_.rl[i].dy1 < rla_.rl[j].dy2&&rla_.rl[i].dy2 >= rla_.rl[j].dy2) is = true;
			}
			if (is) {
				rla_.rv[i].emplace_back(j);
				rla_.rv[j].emplace_back(i);
				rla_.rvid[i].emplace_back(id);
				switch (id)
				{
				case 0:rla_.rvid[j].emplace_back(1+4); break;
				case 1:rla_.rvid[j].emplace_back(0+4); break;
				case 2:rla_.rvid[j].emplace_back(3+4); break;
				case 3:rla_.rvid[j].emplace_back(2+4); break;
				case 8:rla_.rvid[j].emplace_back(8); break;
				}
			}
		}
	}
}

void nextOutput(const roguelikeAll& rla_) {
	for (size_t k = 0; k < rla_.size(); ++k) {
		std::cout << (k + 1) << ':';
		for (size_t i = 0; i < rla_.rv[k].size(); ++i) {
			std::cout << (rla_.rv[k][i] + 1);
			switch (rla_.rvid[k][i])
			{
			case 0:std::cout << 'd';break;
			case 1:std::cout << 'u'; break;
			case 2:std::cout << 'r'; break;
			case 3:std::cout << 'l'; break;
			case 4:std::cout << 'D'; break;
			case 5:std::cout << 'U'; break;
			case 6:std::cout << 'R'; break;
			case 7:std::cout << 'L'; break;
			case 8:std::cout << '?'; break;
			}
			std::cout << ',';
		}
		std::cout << std::endl;
	}
}

constexpr size_t x = 40;
constexpr size_t y = 30;

void roguelikeMain() {
	std::vector<size_t> vint(x*y, 0);
	//ローグライクのデータを管理
	roguelikeAll rla(8);
	//マップを分割
	division(x, y, rla);
	divisionOutput(vint, x, rla);
	//分割したマップに部屋を生成
	room(x, y, rla);
	roomOutput(vint, x, rla);
	//画面へ出力
	//output(vint, x, y);
	//
	next(rla);
	//nextOutput(rla);

	rla.reset();
}

int main() {

	srand((unsigned int)time(nullptr));

	for (size_t i = 0; i < 1000000; ++i) {
		roguelikeMain();
	}


	return 0;
}