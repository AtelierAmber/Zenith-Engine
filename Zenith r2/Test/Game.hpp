#pragma once
#include <interface/IGame.hpp>

class Game :
    public zen::IGame{
public:
    Game();
    ~Game();

protected:
    /* Called on game start
     * Used for scene independent variables */
    virtual void build() override;

    /* Called every game step 
     * Used for scene independent variables */
    virtual void update() override;

    /* Called on game exit
     * Used for game independent variables */
    virtual void destroy() override;

    /// Window m_window;
private:

};

