#include <Windows.h>  

#include <osgViewer/Viewer>  
#include <osgDB/ReadFile>  
#include <osg/Node>  
#include <osg/Matrix>

namespace MatrixTest
{

	class Matrix4_Row
	{
	public:
		Matrix4_Row()
		{
			m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
			m[0][1] = m[0][2] = m[0][3] = 0.0f;
			m[1][0] = m[1][2] = m[1][3] = 0.0f;
			m[2][0] = m[2][1] = m[2][3] = 0.0f;
			m[3][0] = m[3][1] = m[3][2] = 0.0f;
		}

		Matrix4_Row(float m11, float m12, float m13, float m14, // 1st row
			float m21, float m22, float m23, float m24, // 2nd row
			float m31, float m32, float m33, float m34, // 3rd row
			float m41, float m42, float m43, float m44) // 4th row
		{
			m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
			m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
			m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
			m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
		}
	private:
		union
		{
			float m[4][4];
			float mm[16];
		};
	};

	//作者：天律界中子
	//	链接：http ://www.jianshu.com/p/bfc8327eaad3
	//來源：简书
	//	著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

	class Matrix4_Col
	{
	public:
		Matrix4_Col()
		{
			m[0] = m[5] = m[10] = m[15] = 1.0f;
			m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
		}

		Matrix4_Col(float m00, float m01, float m02, float m03, // 1st column
			float m04, float m05, float m06, float m07, // 2nd column
			float m08, float m09, float m10, float m11, // 3rd column
			float m12, float m13, float m14, float m15) // 4th column
		{
			m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;
			m[4] = m04; m[5] = m05; m[6] = m06; m[7] = m07;
			m[8] = m08; m[9] = m09; m[10] = m10; m[11] = m11;
			m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
		}
	private:
		union
		{
			float m[16];
			float mm[4][4];
		};
	};

	//作者：天律界中子
	//	链接：http ://www.jianshu.com/p/bfc8327eaad3
	//來源：简书
	//	著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

}
int main(int argc, char** argv)
{
	/*
	 0, 1, 2, 3,
	 4, 5, 6, 7,
	 8, 9, 10,11,
	 12,13,14,15
	*/
	MatrixTest::Matrix4_Row row(
	0,1,2,3,
	4,5,6,7,
	8,9,10,11,
	12,13,14,15
	);
	MatrixTest::Matrix4_Col col(
		0,4,8,12,
		1,5,9,13,
		2,6,10,14,
		3,7,11,15
	);

	float m[3][2] = {
		1,2,
		3,4,
		5,6
	};
	float m2[6] = { 1,2,3,4,5,6 };
	osgViewer::Viewer view;

	view.setSceneData(osgDB::readNodeFile("cow.osg"));

	view.getCamera()->setViewport(0, 0, 1280, 678);
	osg::Matrix trans;
	trans.makeTranslate(0., 0., -12.);
	osg::Matrix transInv;
	transInv.makeTranslate(0., 0., 12.);
	double angle(0.0);
	
	osg::Vec3 eye, center, up;
	

	while (!view.done())
	{
		view.getCamera()->getViewMatrixAsLookAt(eye, center, up);
		
		view.getCamera()->setProjectionMatrixAsPerspective(75, 1280.0 / 678.0, 0.25, 8000);
		osg::Matrix prjMat = view.getCamera()->getProjectionMatrix();
		double dFov = 0;
		double dRatio = 0;
		double dzNear = 0;
		double dzFar = 0;
		prjMat.getPerspective(dFov, dRatio, dzNear, dzFar);

		//view.getCamera()->setViewport(0, 0, 400, 678);
		
		//osg::Matrix rot;

		osg::Matrix rot;
		rot.makeRotate(angle, osg::Vec3(1.0, 0., 0.));
		angle += 0.01;
		osg::Matrix viewMat = rot*trans;
			viewMat = osg::Matrix::inverse(transInv * rot);
		view.getCamera()->setViewMatrix(viewMat);
		view.frame();
		osg::Camera* pCamera = view.getCamera();
		osg::Matrix projMat = pCamera->getProjectionMatrix();

		// test projectMatrix
		double fov = 45;
		double aspectRatio = 1.0;
		double zNear = 0.5;
		double zFar = 1000;
		projMat.getPerspective(fov, aspectRatio, zNear, zFar);

	}

	return 0;
}