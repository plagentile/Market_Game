#ifndef SYMBOL_H
#define SYMBOL_H

#include <QString>
class Symbol
{
public:
    Symbol();
    Symbol(const Symbol & assign); //may need to delete
    Symbol & operator =(const Symbol & assign) =delete; //may need to delete
    ~Symbol() = default;

    Symbol(const QString symbol, const QString name, const QString country, const QString sector, const QString industry)
       :symbol(symbol), name(name), country(country), sector(sector), industry(industry)
    {
    }
    const QString symbol;
    const QString name;
    const QString country;
    const QString sector;
    const QString industry;
};

#endif // SYMBOL_H
