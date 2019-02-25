##osgearth_fog 案例分析：


1. 解析输入参数：

		osg::ArgumentParser arguments(&argc,argv);
2. 创建Viewer：
		osgViewer::Viewer viewer(arguments);
3. 创建root节点：
		osg::Group* root = new osg::Group();
4. 设置雾效果状态属性
		osg::Fog* fog = new osg::Fog;            
		fog->setColor( viewer.getCamera()->getClearColor() );                
		fog->setDensity( 0.02 );    
		fog->setMode(osg::Fog::LINEAR);
		fog->setStart(5.0);
		fog->setEnd(50.0);
		root->getOrCreateStateSet()->setAttributeAndModes( fog, osg::StateAttribute::ON );
5. 添加雾回调：
		fog->setUpdateCallback(new FogCallback());      
6. 添加一些模型：
		root->addChild(osgDB::readNodeFile("cow.osg")); 
7. 创建shader根节点：
		osg::Group* rootShader = new osg::Group();
		root->addChild(rootShader); 
8. 对节点添加Shader：
		osg::MatrixTransform* mt = new osg::MatrixTransform;    
		osg::Node* cowShader = osgDB::readNodeFile("cow.osg.10,0,0.trans");    
		osgEarth::Registry::instance()->shaderGenerator().run(cowShader); 

9. 添加灯光：
		// Add phong lighting
		   osgEarth::PhongLightingEffect* phong = new osgEarth::PhongLightingEffect;
		   phong->attach(rootShader->getOrCreateStateSet());
		
		   osg::Group* _lights = new osg::Group;
		   osg::LightSource* globalLight = new osg::LightSource;
		   osg::Light* light = globalLight->getLight();
		
		   light->setPosition(osg::Vec4(0.0,0.0,1.0,0.0));
		   light->setAmbient(osg::Vec4(0.0f,0.0f,0.0f,1.0f));
		   light->setDiffuse(osg::Vec4(0.8f,0.8f,0.8f,1.0f));
		   _lights->addChild(globalLight);
		
		   osgEarth::GenerateGL3LightingUniforms visit;
		   _lights->accept(visit);
		
		   rootShader->addChild(_lights); 
		 	osgEarth::GenerateGL3LightingUniforms visit;
		   _lights->accept(visit);
		
		   rootShader->addChild(_lights);
10. 添加雾效果
		// Attach the fog effect so fog will tack effect.
		FogEffect* fogEffect = new FogEffect;
		fogEffect->attach(cowShader->getOrCreateStateSet());
		mt->addChild(cowShader);
		rootShader->addChild(mt);
11. 设置漫游器和数据：
		viewer.setCameraManipulator(new osgGA::TrackballManipulator);
		viewer.setSceneData(root);
  
12. 数据更新和渲染循环：

 float lightFactor = 1.0f;
   float lightAngle = osg::PI/2.0;

   while(!viewer.done())
   {
       // Change light parameters ever 60 frames
       if(viewer.getFrameStamp()->getFrameNumber()%60 == 0)
       {
           lightFactor -= 0.05f;
           if(lightFactor < 0.0f)
           {
               lightFactor = 0.0f;
           }
           lightAngle -= osg::PI/180;
           if(lightAngle <=  -osg::PI)
           {
               lightAngle = osg::PI;
           }

           light->setPosition(osg::Vec4(0.0,cos(lightAngle),sin(lightAngle),0.0));

           // Change fog modes ever 200 frames
           if(viewer.getFrameStamp()->getFrameNumber()%200 == 0)
           {
               fog->setMode(osg::Fog::EXP);
               OE_NOTICE << "switching to osg::Fog::EXP" << std::endl;
           }
           else if(fog->getMode() == osg::Fog::EXP)
           {
                   
                fog->setMode(osg::Fog::EXP2);
                OE_NOTICE << "switching to osg::Fog::EXP2" << std::endl;
           }
           else 
           {
               fog->setMode(osg::Fog::LINEAR);
               OE_NOTICE << "switching to osg::Fog::LINEAR" << std::endl;
           }
            
       }
       viewer.frame();
   }
