#ifndef UPDATABLE_H
#define UPDATABLE_H

#include "Drawable.h"

class Updatable : public Drawable {
    public:
        // inherit constructors
        using Drawable::Drawable;

        virtual void update(float dt);
        virtual void updatePhysics(float dt);

    private:
        
};


#endif // UPDATABLE_H