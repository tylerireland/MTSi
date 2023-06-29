#ifndef __ProjectDisplay_H__
#define __ProjectDisplay_H__

#include "mixr/ui/glut/GlutDisplay.hpp"

// -------------------------------------------------------------------------------
// Class: Display
//
// Description:
//      Derived Display that will make our map page move.
// -------------------------------------------------------------------------------
class ProjectDisplay final : public mixr::glut::GlutDisplay
{
    DECLARE_SUBCLASS(ProjectDisplay, mixr::glut::GlutDisplay)

public:
    ProjectDisplay();

    //void mouseMotionEvent(const int x, const int y) final;
 /*   void mouseEvent(const int button, const int state, const int x, const int y) final;
    void passiveMotionEvent(const int x, const int y) final;*/
    void buttonEvent(const int b) final;
    void updateData(const double dt = 0.0) final;
 /*   void clickEvent(const int button); */

private:
    int startX{};         // startX of our last mouse position
    int startY{};         // startY of our last mouse position
    bool dragging{};      // are we dragging the map?
    int range{};          // range of our map
    SendData rangeSD;
};

#endif
