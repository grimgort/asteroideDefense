#ifndef GOLD_H
#define GOLD_H

#include "TextNode.h"
class Gold
{
    public:
        Gold(int value, const FontHolder& fonts);

    void soustractValue(int value) ;
    void addValue(int value) ;
    int  getValue();
    void updateTexts();



    protected:

    private:
        int m_value ;
        ///> Gold text
        TextNode* m_goldDisplay;
};

#endif // GOLD_H
