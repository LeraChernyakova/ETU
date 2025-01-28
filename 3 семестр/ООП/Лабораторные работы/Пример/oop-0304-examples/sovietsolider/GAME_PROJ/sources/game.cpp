#include "../headers/game.h"
#include <ctype.h>
#include <typeinfo>
#include <vector>
#include "../headers/logger.h"
#include "../headers/fstreamWrapper.h"

#define NUM_OF_ENEMIES 3

template <typename winCondType, typename lossCondType, int difficulty>
void Game<winCondType, lossCondType, difficulty>::clear_terminal_icanon()
{
	static struct termios told, tnew;
	tcgetattr(STDIN_FILENO, &told);
	tnew = told;
	tnew.c_lflag &= ~ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &tnew);
}

template <typename winCondType, typename lossCondType, int difficulty>
void Game<winCondType, lossCondType, difficulty>::set_terminal_icanon()
{
	static struct termios told, tnew;
	tcgetattr(STDIN_FILENO, &told);
	tnew = told;
	tnew.c_lflag |= ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &tnew);
}

template <typename winCondType, typename lossCondType, int difficulty>
void Game<winCondType, lossCondType, difficulty>::clear_screen()
{
	std::cout << "\033[H\033[J";
}

template <typename winCondType, typename lossCondType, int difficulty>
void Game<winCondType, lossCondType, difficulty>::spawn_enemy(std::vector<Enemy*>& enemy_container)
{
	std::mt19937 generator;
    std::random_device rd;
    generator.seed(rd());
    std::uniform_int_distribution<> chooseEn(0, 2);
	
	for(auto i = 0; i<difficulty; i++)
	{
		int choseEnemy = chooseEn(generator);
		std::cout << chooseEn << std::endl;
		if(choseEnemy == 0)
			enemy_container.push_back(new EnemyBoss);
		else if(choseEnemy == 1)
			enemy_container.push_back(new EnemyMove);
		else if(choseEnemy == 2)
			enemy_container.push_back(new EnemyStand);
		std::cout << enemy_container.size() << std::endl;
	}
	

}

template <typename winCondType, typename lossCondType, int difficulty>
void Game<winCondType, lossCondType, difficulty>::Update()
{
	std::ofstream file; 
	FstreamWrapper file_w(file, "gameOut");
	OstreamWrapper cout_w(std::cout);
	Logger::initGlobal({file_w, cout_w});
	FieldView print(*field);

	int input;
	print.display();
	//input = fgetc(stdin);

	clear_screen();
	while(true)
	{
		clear_screen();

		print.display();
		if(winCond.isDone())
		{
			std::cout << "EXIT COND WORKS";
			
			return;
		}
		if(lossCond.isDone())
		{
			std::cout << "Player is Dead";
			return;
		}

		//std::cout << enemy_container.size() << std::endl;
		
		for(int i=0; i<objects_container.size();i++)
		{
			objects_container.at(i)->onPass(player, *field);
			objects_container.at(i)->check_for_death(*field, objects_container, i);
		}
		for(int i=0;i<enemy_container.size();i++)
		{
			enemy_container.at(i)->init_fight(player, *field);
			enemy_container.at(i)->move(player, *field);
			enemy_container.at(i)->check_for_death(*field, enemy_container, i);			
		}
		Logger::getGlobal().display("");
		//input = fgetc(stdin);		//
		//input_controller.set_symb(input);
		input_controller->act();
	}
	set_terminal_icanon();
}

template <typename winCondType, typename lossCondType, int difficulty>
void Game<winCondType, lossCondType, difficulty>::onStart()
{
	clear_terminal_icanon();
	
	field = new Field(20, 20);
	
	objects_container.push_back(new ObjectHeal);
	objects_container.push_back(new ObjectDamage);
	objects_container.push_back(new ObjectRange);

	spawn_enemy(enemy_container);

	Cell& entrance = field->put_exits(2);  //ссылка на вход
	field->put_enemies(enemy_container);
	field->put_object(objects_container);

	player.set_posx(entrance.get_x()); player.set_posy(entrance.get_y()); //coords in player according to entrance
	field->get_cell(player.get_posx(), player.get_posy()).set_display('3');
	entrance.set_player(player);

	input_controller = new InputController(&player, field, &enemy_container);
	//nput_controller.set_field(field);
	//input_controller.set_player(&player);
	//input_controller.set_enemies(&enemy_container);
	input_controller->initialize_binds();
}

template <typename winCondType, typename lossCondType, int difficulty>
std::vector<Enemy*>& Game<winCondType, lossCondType, difficulty>::get_enemies()
{
	return enemy_container;
}

template <typename winCondType, typename lossCondType, int difficulty>
Field& Game<winCondType, lossCondType, difficulty>::get_field()
{
	return *field;
}

template <typename winCondType, typename lossCondType, int difficulty>
Player& Game<winCondType, lossCondType, difficulty>::get_player()
{
	return player;
}

template <typename winCondType, typename lossCondType, int difficulty>
winCondType& Game<winCondType, lossCondType, difficulty>::get_winCond()
{
	return winCond;
}

template <typename winCondType, typename lossCondType, int difficulty>
lossCondType& Game<winCondType, lossCondType, difficulty>::get_lossCond()
{
	return lossCond;
}

template <typename winCondType, typename lossCondType, int difficulty>
Game<winCondType, lossCondType, difficulty>::~Game()
{
	delete field;
	for(int i=0;i<enemy_container.size(); i++)
	{
		delete enemy_container.at(i);
	}
	for(int i=0;i<objects_container.size(); i++)
	{
		delete objects_container.at(i);
	}
	delete input_controller;
}


