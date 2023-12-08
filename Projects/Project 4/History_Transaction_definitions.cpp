#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//

Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,  
        unsigned int month_date,  unsigned year_date, 
        bool buy_sell_trans,  unsigned int number_shares,  
        double trans_amount ){

          symbol = ticker_symbol; 
          day = day_date; 
          month = month_date; 
          year = year_date;         

          if(buy_sell_trans == true){
            trans_type = "Buy"; 
          }

          else{
            trans_type = "Sell";
          }

          shares = number_shares; 
          amount = trans_amount;   

          trans_id = assigned_trans_id++;                    

        };


// Destructor
// TASK 1
//
Transaction::~Transaction(){

}

// Overloaded < operator.
// TASK 2
//

bool Transaction::operator<(Transaction const &other){
  if(get_year() < other.get_year()){
    return true; 
  }

  else if((get_year() == other.get_year()) && (get_month() < other.get_month())){
    return true; 
  }

  else if((get_year() == other.get_year()) && (get_month() == other.get_month()) && (get_day() < other.get_day())){
    return true; 
  }
 
  else if((get_year() == other.get_year()) && (get_month() == other.get_month()) && (get_day() == other.get_day()) && (get_trans_id() > other.get_trans_id())){
    return true; 

  }

  else{
    return false; 

  }

}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 1
//
History::History():
   p_head{nullptr}

  {

};

// Destructor
// TASK 2
//
History::~History(){

  while(p_head != nullptr){
    Transaction *tmp{get_p_head()}; 
    p_head = p_head->get_next();
    delete tmp; 

  }

}


// read_history(...): Read the transaction history from file.
// TASK 4
//
void History::read_history(){
  ece150::open_file(); 

  while(ece150::next_trans_entry()){
    Transaction *p_new_trans{new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount())};
    insert(p_new_trans); 

  }

  ece150::close_file(); 

}

// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert(Transaction *p_new_trans){
  
  if(p_head == nullptr){
    p_head = p_new_trans; 

  }

  else{
    Transaction *p_foot{p_head}; 

    while(p_foot->get_next() != nullptr){
      p_foot = p_foot->get_next(); 

    }

    p_foot->set_next(p_new_trans); 

  }

}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date(){

  for(Transaction *tmp{p_head}; tmp->get_next() != nullptr; tmp = tmp->get_next()){
    Transaction *min_adr{tmp}; 
    Transaction min_value{*tmp};

    for(Transaction *tmp2{tmp->get_next()}; tmp2->get_next() != nullptr; tmp2 = tmp2->get_next()){

      if((min_adr->get_year() >= tmp2->get_year()) && (min_adr->get_month() >= tmp2->get_month()) && (min_adr->get_day() > tmp2->get_day())){
        min_value = *tmp2;  
        min_adr = tmp2; 

      }

      else{

      }
    }

    Transaction tmp_swap_value{*tmp}; 
    *tmp = min_value;
    *min_adr = tmp_swap_value; 
  }

}

// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History::update_acb_cgl(){

  double ACB{0}; 
  int share_balance{0}; 
  double prev_acb_share{0}; 

  for(Transaction *tmp{p_head}; tmp->get_next() != nullptr; tmp = tmp->get_next()){
 
    if(tmp->get_trans_type() == true){
      ACB = ACB + tmp->get_amount();
      tmp->set_acb(ACB);  

      share_balance = share_balance + tmp->get_shares(); 
      tmp->set_share_balance(share_balance); 

      tmp->set_acb_per_share(tmp->get_acb()/tmp->get_shares());
      
      tmp->set_cgl(0.0); 

      prev_acb_share = tmp->get_acb_per_share();

    }

    else{

      ACB = ACB - tmp->get_shares()*prev_acb_share; 
      tmp->set_acb(ACB); 

      share_balance = share_balance - tmp->get_shares(); 
      tmp->set_share_balance(share_balance); 

      tmp->set_acb_per_share(prev_acb_share);

      tmp->set_cgl(tmp->get_amount() - tmp->get_shares()*tmp->get_acb_per_share()); 

      prev_acb_share = tmp->get_acb_per_share();

    }
  } 

}


// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year){

  double total_cgl{0}; 

  for(Transaction *tmp{p_head}; tmp->get_next() != nullptr; tmp = tmp->get_next()){
    
    if(tmp->get_year() > year){
      break; 
    }

    else{
      total_cgl = total_cgl + tmp->get_cgl();  

    }

  }

  return total_cgl; 
  
}



// print() Print the transaction history.
//TASK 9
//
void History::print(){
  Transaction *current{p_head}; 

  std::cout << "========== BEGIN TRANSACTION HISTORY ==========" << std::endl;

  while(current != nullptr){
    current->print(); 
    current = current->get_next(); 
  }

  std::cout << "========== END TRANSACTION HISTORY ==========" << std::endl; 

}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
