#include <iostream>
#include <random>
#include <map>

void showInfo(std::map<std::string, double> m)
{
	for (auto& p : m)
	{
		std::cout << p.first << ":" << p.second << " ";
	}
}
int main()
{
	setlocale(0, "rus");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0.95, 1.05);

	std::map<std::string, double> MyMoney;
	std::map<std::string, double> BankMoney;
	std::map<std::string, double> Exchange;
	MyMoney["RUB"] = 1e6;	BankMoney["RUB"] = 10000;	Exchange["RUB/USD"] = 0.011; Exchange["USD/RUB"] = 90.9;
	MyMoney["EUR"] = 0;     BankMoney["EUR"] = 1000;	Exchange["RUB/EUR"] = 0.01;	 Exchange["EUR/RUB"] = 100;
	MyMoney["USD"] = 0;     BankMoney["USD"] = 1000;	Exchange["USD/EUR"] = 0.9;	 Exchange["EUR/USD"] = 1.1;
	MyMoney["USDT"] = 0;    BankMoney["USDT"] = 1000;	Exchange["USD/USDT"] = 1;	 Exchange["USDT/USD"] = 1;
	MyMoney["BTC"] = 0;     BankMoney["BTC"] = 1.5;		Exchange["USD/BTC"] = 0.000017; Exchange["BTC/USD"] = 58823, 529;
	while (true)
	{

		std::cout << "Введите запрос в формате: имеющаяся валюта/желаемая валюта, например RUB/USD\n" << "введите exit для выхода\n";
		std::string request;
		std::cin >> request;
		if (request == "exit")
		{
			return 0;
		}
		if (request.find("/") == -1 || request.size() != 7)
		{
			std::cout << "Ошибка ввода запроса\n";
		}
		else
		{
			std::string simple = request.substr(0, 3);
			std::string second = request.substr(4, 6);
			std::map<std::string, double>::iterator it1 = MyMoney.find(simple);
			std::map<std::string, double>::iterator it2 = BankMoney.find(second);
			std::map<std::string, double>::iterator it3 = Exchange.find(request);
			if (it1 == MyMoney.end() || it2 == BankMoney.end() || it3 == Exchange.end())
			{
				std::cout << "Не найдена соответствующая валютная пара\n";
			}
			else
			{
				std::cout << "Введите кол-во валюты, которое вы хотели бы обменять: ";
				double count;
				std::cin >> count;
				std::cout << "Мои деньги: ";
				showInfo(MyMoney);
				std::cout << "\n";
				std::cout << "Деньги банка: ";
				showInfo(BankMoney);

				std::cout << "\nкурс текущей валюты:" << Exchange[request] << "\n";

				std::cout << "\n\n";

				if (MyMoney[simple] < count)
				{
					std::cout << "Недостаточно денег на счете\n\n";
				}
				else if (BankMoney[second] < count * Exchange[request])
				{
					std::cout << "Недостаточно денег в банке\n\n";
				}
				else
				{
					std::cout << "Валюта после обмена:\n";
					MyMoney[simple] -= count;
					MyMoney[second] += count * Exchange[request];
					BankMoney[simple] += count;
					BankMoney[second] -= count * Exchange[request];
					for (auto& p : Exchange)
					{
						p.second *= dist(gen);
					}
					std::cout << "Мои деньги: ";
					showInfo(MyMoney);
					std::cout << "\n";
					std::cout << "Деньги банка: ";
					showInfo(BankMoney);
					std::cout << "\nкурс текущей валюты:";
					std::cout << Exchange[request] << "\n\n";
				}
			}
		}
	}
	return 0;
}