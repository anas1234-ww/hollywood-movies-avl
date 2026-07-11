#include <iostream>
#include "Avl-tree.h"
#include "movie.h"
#include "movie.cpp"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
int main(){
				Movie films("/storage/emulated/0/HollywoodMovies/HollywoodMovies.csv");
				int choice;
				do {
								std::cout << "==== Hollywood Movie Management System ==== " << std::endl;
   std::cout << "=1. Search for a movie by ID" << std::endl;
   std::cout << "2. View all movies (sorted by ID)" << std::endl;
   std::cout << "3. Compare search speed (Linear vs AVL)" << std::endl;
   std::cout << "4. View top movie" << std::endl;
   std::cout << "5. View movies from a specific year" << std::endl;
   std::cout << "6. General statistics (average budget, highest-grossing movie, etc.)" << std::endl;
								std::cout << "7.exit" << std::endl;
								std::cin >> choice;
																switch (choice){
												case 1:{
																system("clear");
films.Search_film_employment();
																break;
												}
												case 2:{
																system("clear");
films.show_movie_employment()	;
      break;
												}
												case 3:{
																system("clear");
films.Comparison_Avl_liner_employment()	;
      break;
												}	
     case 4:{
																system("clear");
films.show_best_movie_employment();
      break;
												}
     case 5:{
																system("clear");
films.Show_films_specific_year_employment();
      break;
												}
     case 6:{
																system("clear");
films.General_statistics_employment();
      break;
												}	
     default:
																				std::cout << "Enter one of the good things" << std::endl;
																				break;
								}
				}while(choice != 7);
				return 0;
}