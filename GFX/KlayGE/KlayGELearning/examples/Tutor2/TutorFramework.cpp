#include "TutorFramework.h"

TutorFramework::TutorFramework()
    : App3DFramework("Tutor2")
{
}

void TutorFramework::OnCreate()
{
    font_ = KlayGE::SyncLoadFont("gkai00mp.kfont");
    auto& root_node = KlayGE::Context::Instance().SceneManagerInstance().SceneRootNode();
   
    { // create cube
        /*
        * 首先构建的是预设的辅助几何体，例如三角条带组成的立方体RenderableTriBox，它的输入参数为一个由最小 / 最大坐标
        * 构建的Box对象，以及立方体的颜色。KlayGE中的所有可视物体（即Renderable的派生类，包括RenderableTriBox等）
        * 都必须对应有RenderTechnique，即渲染这个对象的方法——通常从FX文件中读取并获得
        */
        KlayGE::OBBox boxRange(
            KlayGE::MathLib::convert_to_obbox(KlayGE::AABBox(KlayGE::float3(-1.0f, -0.25f, -0.25f), KlayGE::float3(-0.5f, 0.25f, 0.25f))));
        KlayGE::Color boxColor(1.0f, 0.0f, 0.0f, 1.0f);

        /*
        构建一个场景节点，并使用添加到场景管理器中，从而在窗口中进行渲染
        SceneObjectHelper的传入参数除了辅助几何体的实例以外，还有一个属性参数，它的取值可以为：
        SOA_Cullable：这个对象参与裁减。即，当它位于视锥体之外时，它会被自动排除出渲染队列之外，从而降低渲染负担。
                      如果没有设置这一参数，那么系统将总是渲染这个对象，无论它是否在可见区域之内
        SOA_Overlay：这个对象的渲染始终位于其它对象之前，即覆盖在默认场景之上
        SOA_Moveable：这个对象是可以移动的。此时系统在计算它是否位于视锥体内时，会将GetModelMatrix()考虑在结果当中
        SOA_Unvisible：这个对象是不可见的
        */
        renderableBox_ = KlayGE::MakeSharedPtr<KlayGE::SceneNode>(
            KlayGE::MakeSharedPtr<KlayGE::RenderableComponent>(
                KlayGE::MakeSharedPtr<KlayGE::RenderableTriBox>(boxRange, boxColor)),
            KlayGE::SceneNode::SOA_Cullable);
      //  root_node.AddChild(renderableBox_);
    }
   
    { // load mesh from file
         /*
        第二个要构建的几何体，从teapot.glb文件中读取（这里的teapot.glb保存在Samples/media/Common目录下）
        LoadModel()的第一个参数为文件名，第二个参数影响了D3D11下的数据访问策略（在OpenGL下无用处），
        第三个参数指定裁剪方式，之后的两个参数指定模型和网格数据对象实例的构建方法。
        注意这里的RenderPolygon就是我们之前自定义的StaticMesh派生类
    */
       KlayGE::RenderModelPtr loadedModel = KlayGE::SyncLoadModel("teapot.glb", KlayGE::EAH_GPU_Read,
            KlayGE::SceneNode::SOA_Cullable, KlayGE::AddToSceneRootHelper,
            KlayGE::CreateModelFactory<KlayGE::RenderModel>, KlayGE::CreateMeshFactory<RenderPolygon>);

        renderableFile_ = loadedModel->RootNode();
        renderableFile_->TransformToParent(KlayGE::MathLib::translation(0.0f, 0.5f, 0.0f));
    }
  
   
    { // custom mesh
        // 定义一串顶点数据，以及用户绘制这些顶点所需的图元和索引数据
        // 这里我们将试图通过8个顶点来绘制一个完整的立方体
        std::vector<KlayGE::float3> vertices;
        vertices.emplace_back(0.5f, -0.25f, 0.25f);
        vertices.emplace_back(1.0f, -0.25f, 0.25f);
        vertices.emplace_back(1.0f, -0.25f, -0.25f);
        vertices.emplace_back(0.5f, -0.25f, -0.25f);
        vertices.emplace_back(0.5f, 0.25f, 0.25f);
        vertices.emplace_back(1.0f, 0.25f, 0.25f);
        vertices.emplace_back(1.0f, 0.25f, -0.25f);
        vertices.emplace_back(0.5f, 0.25f, -0.25f);

        // 首先需要构建一个几何体模型RenderModel，它是所有StaticMesh，也就是静态网格的载体。一个RenderModel可以包含
        // 一个或多个网格对象，每个网格对象都有自己的MaterialID（材质ID），RenderTechnique等属性
        KlayGE::RenderModelPtr model = KlayGE::MakeSharedPtr<KlayGE::RenderModel>(L"model", KlayGE::SceneNode::SOA_Cullable);
        std::vector<KlayGE::StaticMeshPtr> meshes(2);
        std::vector<KlayGE::uint16_t> indices1;
        std::vector<KlayGE::uint16_t> indices2;

        indices1.push_back(0); indices1.push_back(4); indices1.push_back(1); indices1.push_back(5);
        indices1.push_back(2); indices1.push_back(6); indices1.push_back(3); indices1.push_back(7);
        indices1.push_back(0); indices1.push_back(4);;

        // 生成立方体的侧面网格
        meshes[0] = KlayGE::MakeSharedPtr<RenderPolygon>(L"side_mesh");
        meshes[0]->NumLods(1);
        // 将顶点数据的地址和大小传递给网格对象，并指定元素类型，以及D3D11下的数据访问策略
       // 这里的元素类型vertex_element由三个参数组成：
       // 第一个VEU_Position即顶点属性类型，除了顶点坐标之外，还可以为法线VEU_Normal，纹理坐标VEU_TextureCoord等等
       // 第二个参数为索引值，对于纹理坐标属性，它表示该纹理坐标对应的纹理通道
       // 第三个参数表示数据的类型，例如EF_GR32F（float2），EF_BGR32F（float3），EF_ABGR32F（float4）等

        meshes[0]->AddVertexStream(0,&vertices[0],static_cast<KlayGE::uint32_t>(sizeof(vertices[0])*vertices.size()),
            KlayGE::VertexElement(KlayGE::VEU_Position, 0, KlayGE::EF_BGR32F), KlayGE::EAH_GPU_Read);

        // 将索引数据的地址和大小传递给网格对象，此外还有索引数据的类型（EF_R16UI表示16位无符号整数）和数据访问策略
        meshes[0]->AddIndexStream(0, &indices1[0], static_cast<KlayGE::uint32_t>(sizeof(indices1[0]) * indices1.size()),
            KlayGE::EF_R16UI, KlayGE::EAH_GPU_Read);

        // 设置图元的绘制方式，这里我们设置立方体侧面采取三角条带化的方法进行表达
        meshes[0]->GetRenderLayout().TopologyType(KlayGE::RenderLayout::TT_TriangleStrip);
        meshes[0]->PosBound(KlayGE::AABBox(KlayGE::float3(-1, -1, -1), KlayGE::float3(1, 1, 1)));

        indices2.push_back(0); indices2.push_back(1); indices2.push_back(2);
        indices2.push_back(0); indices2.push_back(2); indices2.push_back(3);
        indices2.push_back(7); indices2.push_back(6); indices2.push_back(5);
        indices2.push_back(7); indices2.push_back(5); indices2.push_back(4);

        // 底部和顶部网格
        meshes[1] = KlayGE::MakeSharedPtr<RenderPolygon>(L"cap_mesh");
        meshes[1]->NumLods(1);
        meshes[1]->AddVertexStream(0, &vertices[0], static_cast<KlayGE::uint32_t>(sizeof(vertices[0]) * vertices.size()),
            KlayGE::VertexElement(KlayGE::VEU_Position, 0, KlayGE::EF_BGR32F), KlayGE::EAH_GPU_Read);
        meshes[1]->AddIndexStream(0, &indices2[0], static_cast<KlayGE::uint32_t>(sizeof(indices2[0]) * indices2.size()),
            KlayGE::EF_R16UI, KlayGE::EAH_GPU_Read);
        meshes[1]->GetRenderLayout().TopologyType(KlayGE::RenderLayout::TT_TriangleList);
        meshes[1]->PosBound(KlayGE::AABBox(KlayGE::float3(-1, -1, -1), KlayGE::float3(1, 1, 1)));
        
        for (size_t i = 0; i < meshes.size(); ++i)
        {
            meshes[i]->BuildMeshInfo(*model);
        }
        // 将所有的网格对象传递给RenderModel几何模型
        model->AssignMeshes(meshes.begin(), meshes.end());
        model->BuildModelInfo();
        renderableMesh_ = model->RootNode();
      
        //将几何模型传递给场景对象，加入到场景当中
        for (size_t i = 0; i < meshes.size(); ++i)
        {
           renderableMesh_->AddComponent(KlayGE::MakeSharedPtr<KlayGE::RenderableComponent>(meshes[i]));
        }
       root_node.AddChild(renderableMesh_);
    }

    // create axis
    {
        std::vector<KlayGE::float3> vertices;
        vertices.emplace_back(0.0f, 0.0f, 0.0f); // origin
        vertices.emplace_back(2.0f, 0.0f, 0.0f); // +x;
        vertices.emplace_back(0.0f, 2.0f, 0.0f); // +y;
        vertices.emplace_back(0.0f, 0.0f, 2.0f); // +z;
     
        KlayGE::RenderModelPtr axis = KlayGE::MakeSharedPtr<KlayGE::RenderModel>(L"Axis", KlayGE::SceneNode::SOA_Cullable);
        std::vector<KlayGE::uint16_t> indices;
        indices.push_back(0); indices.push_back(1);
        indices.push_back(0); indices.push_back(2);
        indices.push_back(0); indices.push_back(3);
       

        std::vector<KlayGE::StaticMeshPtr> meshes(2);
        meshes[0] = KlayGE::MakeSharedPtr<RenderLine>(L"axis");
        KlayGE::StaticMeshPtr& mesh = meshes[0];
        mesh->NumLods(1);
        mesh->AddVertexStream(0, &vertices[0], static_cast<KlayGE::uint32_t>(sizeof(vertices[0])* vertices.size()),
            KlayGE::VertexElement(KlayGE::VEU_Position, 0, KlayGE::EF_BGR32F), KlayGE::EAH_GPU_Read);
        mesh->AddIndexStream(0, &indices[0], static_cast<KlayGE::uint32_t>(sizeof(indices[0])* indices.size()),
            KlayGE::EF_R16UI, KlayGE::EAH_GPU_Read);
        mesh->GetRenderLayout().TopologyType(KlayGE::RenderLayout::TT_LineList);
        mesh->PosBound(KlayGE::AABBox(KlayGE::float3(0,0,0), KlayGE::float3(2, 2, 2)));
        mesh->BuildMeshInfo(*axis);

        // 将所有的网格对象传递给RenderModel几何模型
        axis->AssignMeshes(meshes.begin(),meshes.end());
        axis->BuildModelInfo();

        renderableAxis_ = axis->RootNode();
        renderableAxis_->AddComponent(KlayGE::MakeSharedPtr<KlayGE::RenderableComponent>(mesh));
        root_node.AddChild(renderableAxis_);
    }
    // set camera lookAt
    this->LookAt(KlayGE::float3(0, 0, -4.0f), KlayGE::float3(0, 0, 0));
    this->Proj(0.1f, 20.0f);

    tbController_.AttachCamera(this->ActiveCamera());
    tbController_.Scalers(0.01f, 0.05f);
}

void TutorFramework::DoUpdateOverlay()
{
    // 将当前的FPS信息输出到字符串中，以备渲染到屏幕上
    std::wostringstream stream;
    stream.precision(2);
    stream << std::fixed << this->FPS() << " FPS";

    // 使用之前构建的新字体来渲染文本信息，RenderText()可以接受的参数包括：
    // X，Y位置，KlayGE::Color颜色，std::wstring类型的字符串，以及字体大小
    font_->RenderText(0, 0, KlayGE::Color(1, 1, 0, 1), L"自定义框架例子", 16);
    font_->RenderText(0, 18, KlayGE::Color(1, 1, 0, 1), stream.str(), 16);
}

KlayGE::uint32_t TutorFramework::DoUpdate(KlayGE::uint32_t pass)
{
    // 获取渲染引擎对象。根据KlayGE.cfg文件的配置内容，它可能通过OpenGL或者D3D11来实现
    KlayGE::RenderEngine& re = KlayGE::Context::Instance().RenderFactoryInstance().RenderEngineInstance();
    re.CurFrameBuffer()->Clear(KlayGE::FrameBuffer::CBM_Color | KlayGE::FrameBuffer::CBM_Depth,
        KlayGE::Color(0.2f, 0.4f, 0.6f, 1), 1.0f, 0);

#define USE_OSG_CLEAR 0
#if USE_OSG_CLEAR
    KlayGE::Color clear_clr(0.2f, 0.2f, 0.6f, 1);
    if (KlayGE::Context::Instance().Config().graphics_cfg.gamma)
    {
        float gamma = 2.2f;
        clear_clr.r() = pow(0.26f, gamma);
        clear_clr.g() = pow(0.26f, gamma);
        clear_clr.b() = pow(0.425f, gamma);

    }
#else
    KlayGE::Color clear_clr(0.2f, 0.4f, 0.6f, 1);
    if (KlayGE::Context::Instance().Config().graphics_cfg.gamma)
    {
        clear_clr.r() = 0.029f;
        clear_clr.g() = 0.133f;
        clear_clr.b() = 0.325f;
    }
#endif 
    re.CurFrameBuffer()->Clear(KlayGE::FrameBuffer::CBM_Color | KlayGE::FrameBuffer::CBM_Depth, clear_clr, 1.0f, 0);
    return KlayGE::App3DFramework::URV_NeedFlush | KlayGE::App3DFramework::URV_Finished;
}


RenderPolygon::RenderPolygon(std::wstring_view name)
    : KlayGE::StaticMesh(name)
{
    KlayGE::RenderEffectPtr effect = KlayGE::SyncLoadRenderEffect("RenderableHelper.fxml");

    this->Technique(effect, effect->TechniqueByName("HelperTec"));

    *(effect->ParameterByName("color")) = KlayGE::float4(1.0f, 0.0f, 0.0f, 1.0f);
}

void RenderPolygon::DoBuildMeshInfo(KlayGE::RenderModel const& model)
{
    KFL_UNUSED(model);

    KlayGE::AABBox const& pos_bb = this->PosBound();
    *(effect_->ParameterByName("pos_center")) = pos_bb.Center();
    *(effect_->ParameterByName("pos_extent")) = pos_bb.HalfSize();
}

RenderLine::RenderLine(std::wstring_view name)
    : KlayGE::StaticMesh(name)

{
    KlayGE::RenderEffectPtr effect = KlayGE::SyncLoadRenderEffect("RenderableHelper.fxml");

    this->Technique(effect, effect->TechniqueByName("LineTec"));

    *(effect->ParameterByName("color")) = KlayGE::float4(1.0f, 1.0f, 0.0f, 1.0f);

}

void RenderLine::DoBuildMeshInfo(KlayGE::RenderModel const& model)
{
    KFL_UNUSED(model);

    KlayGE::AABBox const& pos_bb = this->PosBound();
    *(effect_->ParameterByName("pos_center")) = pos_bb.Center();
    *(effect_->ParameterByName("pos_extent")) = pos_bb.HalfSize();
}
