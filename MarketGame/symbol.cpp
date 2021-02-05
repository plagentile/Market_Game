#include "symbol.h"


Symbol::Symbol()
    :symbol(""), name(""), country(""), sector(""), industry("")
{

}

Symbol::Symbol(const Symbol &assign)
    :symbol(assign.symbol), name(assign.name), country(assign.country), sector(assign.sector), industry(assign.industry)
{
}

