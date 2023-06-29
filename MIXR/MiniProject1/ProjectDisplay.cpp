
#include "ProjectDisplay.hpp"
#include "MyPager.hpp"
#include <GL/glut.h>

IMPLEMENT_SUBCLASS(ProjectDisplay, "ProjectDisplay")
EMPTY_SLOTTABLE(ProjectDisplay)
EMPTY_DELETEDATA(ProjectDisplay)

ProjectDisplay::ProjectDisplay()
{
    STANDARD_CONSTRUCTOR()
}

void ProjectDisplay::copyData(const ProjectDisplay& org, const bool)
{
    BaseClass::copyData(org);

    startX = org.startX;
    startY = org.startY;
    dragging = org.dragging;
    range = org.range;
    rangeSD.empty();
}

//// ----------------------------------------------------------------------------
//// sets our start position.
//// ----------------------------------------------------------------------------
//void ProjectDisplay::mouseEvent(const int button, const int state, const int x, const int y)
//{
//    BaseClass::mouseEvent(button, state, x, y);
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) { dragging = false; }
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !dragging) { dragging = true; }
//}
//
//void ProjectDisplay::passiveMotionEvent(const int x, const int y)
//{
//    BaseClass::passiveMotionEvent(x, y);
//    if (!dragging) {
//        startX = x;
//        startY = y;
//    }
//}

//void ProjectDisplay::mouseMotionEvent(const int x, const int y)
//{
//    if (dragging) {
//        const auto page = static_cast<MyPager*>(subpage());
//        if (page != nullptr) {
//            // get our ref lat, because we won't go passed 70 degrees lat (either way);
//            const double lat{ page->getReferenceLatDeg() };
//            if (lat < 70 && lat > -70) {
//                page->moveMap(startX, startY, x, y);
//            }
//            else {
//                if (lat > 0) page->setReferenceLatDeg(65);
//                else page->setReferenceLatDeg(-65);
//            }
//            startX = x;
//            startY = y;
//        }
//    }
//    setMouse(x, y);
//}

//void ProjectDisplay::clickEvent(const int button)
//{
//    if (button == GLUT_LEFT_BUTTON)
//    {
//        
//    }
//
//}

void ProjectDisplay::buttonEvent(const int b)
{
    const auto page = static_cast<MyPager*>(subpage());
    if (page != nullptr) {
        if (b == 1001) {
            std::cout << "click click click";
        }
    }
}

void ProjectDisplay::updateData(const double dt)
{
    BaseClass::updateData(dt);

    const auto page = static_cast<MyPager*>(subpage());
    /*if (page != nullptr) range = static_cast<int>(page->getRange());*/

    send("range", UPDATE_VALUE, range, rangeSD);
}
