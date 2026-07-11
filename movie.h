#pragma once
#include "Avl-tree.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
/*​stod() to double / stof() to float / stoi() to int*/
struct str_film{
    /* Définition des variables */
      int id;
      std::string title;
      std::string LeadStudio;
      int RottenTomatoes;
      int AudienceScore;
      std::string Story;
      std::string Genre;
      int TheatersOpenWeek;
      float OpeningWeekend;
      int BOAvgOpenWeekend;
      float DomesticGross;
      float ForeignGross;
      float WorldGross;
      int Budget;
      float Profitability;
      float OpenProfit;
      int Year;
      str_film();
};
class Movie{
    private:
      TreeNode<str_film>* root = nullptr;
      std::vector<TreeNode<str_film>*>
    ines_film_vec;
      Avl<str_film> tree;
      TreeNode<str_film>* Download_data(std::string& file_name);
      TreeNode<str_film>* Search_film(int ID);
      void insert_Nodes_vector(TreeNode<str_film>* root);
      void show_movie(TreeNode<str_film>* root);
      void Comparison_Avl_liner(TreeNode<str_film>* root , int ser_id);
TreeNode<str_film>* show_best_movie(TreeNode<str_film>* root);
      TreeNode<str_film>*  Show_films_specific_year(int year , TreeNode<str_film>* root);
      void General_statistics(TreeNode<str_film>* root);
    
    public:
      Movie(std::string file_name);
      void Search_film_employment();
      void show_movie_employment();
      void  show_best_movie_employment();
      void Comparison_Avl_liner_employment();
    void  Show_films_specific_year_employment();
      void General_statistics_employment();
};