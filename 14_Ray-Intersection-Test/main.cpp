//
//  main.cpp
//  HCI571-Ray-Intersection-Test
//
//  This code demonstrate the ray-intersection-test functionality.
//
//  Created by Dr Rafael Radkowski on 4/1/13.
//  Copyright (c) 2013 Dr.-Ing. Rafael Radkowski. All rights reserved.
//

#include <iostream>



#include <osg/Group>
#include <osg/MatrixTransform>
#include <osgDB/ReaderWriter>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>

#include "MoveableObject.h"
#include "KeyboardEventHandler.h"


#include "HUD.h"

/*!
 Function to add a hud onto the display
 */
osg::Group* addHUD(void);

int IntersectTraversalMask = 0x3;


/*!
 Main
 */
int main(int argc, const char * argv[])
{

    osg::Group* root = new osg::Group();
    
    osg::Group* collider_group = new osg::Group();
    collider_group->setNodeMask(IntersectTraversalMask);
    
    root->addChild(collider_group);
    
    /////////////////////////////////////////////////////////
    // Load the underground
#ifdef WIN32
    osg::Group* underground = (osg::Group*)osgDB::readNodeFile("../data_art/underground.3ds");
#else
    osg::Group* underground = (osg::Group*)osgDB::readNodeFile("../data_art/underground.3ds");
#endif
    if(underground != NULL)
    {
        collider_group->addChild(underground);
        underground->setNodeMask(IntersectTraversalMask);
    }
    
    /////////////////////////////////////////////////////////
    // Load a moveable object
#ifdef WIN32
    MoveableObject* teapot = new MoveableObject("../data_art/teapot.3ds",collider_group );
#else
    MoveableObject* teapot = new MoveableObject("../data_art/teapot.3ds",collider_group );
#endif
    if(teapot != NULL)
    {
        root->addChild(teapot);
    
        // Set a start position
        teapot->setMatrix(osg::Matrix::translate(0.0, 0.0, 300.0));
    }
    
    // Info hud
    root->addChild(addHUD());
    
    /////////////////////////////////////////////////////////
    // Init the viewer
    osgViewer::Viewer* viewer = new osgViewer::Viewer();
	viewer->setSceneData( root );
	viewer->setUpViewOnSingleScreen(0);
    viewer->setCameraManipulator(new osgGA::TrackballManipulator());
    viewer->getCamera()->setClearColor(osg::Vec4(0.5, 0.5, 1.0, 1.0)) ;
    viewer->addEventHandler(new KeyboardEventHandler(teapot));
    viewer->init();

    /////////////////////////////////////////////////////////
    // Start the viewer
    viewer->run();
    

    return 0;
}

/*
 This helper function adds a heads up display with a text info
 */
osg::Group* addHUD(void)
{
    HUD* hud = new HUD();
    
    osg::ref_ptr<osgText::Text> text = new osgText::Text();
    text->setText("Press 1 to restart");
    text->setAxisAlignment(osgText::Text::SCREEN);
    text->setPosition(osg::Vec3(50.0, 50.0, 0.0));
    text->setCharacterSize(40.0);
    text->setFont("../data_art/arial.ttf");
    text->setColor(osg::Vec4(1.0, 0.0, 0.0, 0.7));
    
    osg::ref_ptr<osg::Group>  textGroup = new osg::Group();
    osg::ref_ptr<osg::Geode>  textGeode = new osg::Geode();
    textGeode->addDrawable(text);
    textGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    textGroup->addChild(textGeode);
    hud->addChild(textGroup);
    
    
    return hud;
}


