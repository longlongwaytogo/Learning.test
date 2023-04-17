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
        * ���ȹ�������Ԥ��ĸ��������壬��������������ɵ�������RenderableTriBox�������������Ϊһ������С / �������
        * ������Box�����Լ����������ɫ��KlayGE�е����п������壨��Renderable�������࣬����RenderableTriBox�ȣ�
        * �������Ӧ��RenderTechnique������Ⱦ�������ķ�������ͨ����FX�ļ��ж�ȡ�����
        */
        KlayGE::OBBox boxRange(
            KlayGE::MathLib::convert_to_obbox(KlayGE::AABBox(KlayGE::float3(-1.0f, -0.25f, -0.25f), KlayGE::float3(-0.5f, 0.25f, 0.25f))));
        KlayGE::Color boxColor(1.0f, 0.0f, 0.0f, 1.0f);

        /*
        ����һ�������ڵ㣬��ʹ����ӵ������������У��Ӷ��ڴ����н�����Ⱦ
        SceneObjectHelper�Ĵ���������˸����������ʵ�����⣬����һ�����Բ���������ȡֵ����Ϊ��
        SOA_Cullable������������ü�����������λ����׶��֮��ʱ�����ᱻ�Զ��ų�����Ⱦ����֮�⣬�Ӷ�������Ⱦ������
                      ���û��������һ��������ôϵͳ��������Ⱦ��������������Ƿ��ڿɼ�����֮��
        SOA_Overlay������������Ⱦʼ��λ����������֮ǰ����������Ĭ�ϳ���֮��
        SOA_Moveable����������ǿ����ƶ��ġ���ʱϵͳ�ڼ������Ƿ�λ����׶����ʱ���ὫGetModelMatrix()�����ڽ������
        SOA_Unvisible����������ǲ��ɼ���
        */
        renderableBox_ = KlayGE::MakeSharedPtr<KlayGE::SceneNode>(
            KlayGE::MakeSharedPtr<KlayGE::RenderableComponent>(
                KlayGE::MakeSharedPtr<KlayGE::RenderableTriBox>(boxRange, boxColor)),
            KlayGE::SceneNode::SOA_Cullable);
      //  root_node.AddChild(renderableBox_);
    }
   
    { // load mesh from file
         /*
        �ڶ���Ҫ�����ļ����壬��teapot.glb�ļ��ж�ȡ�������teapot.glb������Samples/media/CommonĿ¼�£�
        LoadModel()�ĵ�һ������Ϊ�ļ������ڶ�������Ӱ����D3D11�µ����ݷ��ʲ��ԣ���OpenGL�����ô�����
        ����������ָ���ü���ʽ��֮�����������ָ��ģ�ͺ��������ݶ���ʵ���Ĺ���������
        ע�������RenderPolygon��������֮ǰ�Զ����StaticMesh������
    */
       KlayGE::RenderModelPtr loadedModel = KlayGE::SyncLoadModel("teapot.glb", KlayGE::EAH_GPU_Read,
            KlayGE::SceneNode::SOA_Cullable, KlayGE::AddToSceneRootHelper,
            KlayGE::CreateModelFactory<KlayGE::RenderModel>, KlayGE::CreateMeshFactory<RenderPolygon>);

        renderableFile_ = loadedModel->RootNode();
        renderableFile_->TransformToParent(KlayGE::MathLib::translation(0.0f, 0.5f, 0.0f));
    }
  
   
    { // custom mesh
        // ����һ���������ݣ��Լ��û�������Щ���������ͼԪ����������
        // �������ǽ���ͼͨ��8������������һ��������������
        std::vector<KlayGE::float3> vertices;
        vertices.emplace_back(0.5f, -0.25f, 0.25f);
        vertices.emplace_back(1.0f, -0.25f, 0.25f);
        vertices.emplace_back(1.0f, -0.25f, -0.25f);
        vertices.emplace_back(0.5f, -0.25f, -0.25f);
        vertices.emplace_back(0.5f, 0.25f, 0.25f);
        vertices.emplace_back(1.0f, 0.25f, 0.25f);
        vertices.emplace_back(1.0f, 0.25f, -0.25f);
        vertices.emplace_back(0.5f, 0.25f, -0.25f);

        // ������Ҫ����һ��������ģ��RenderModel����������StaticMesh��Ҳ���Ǿ�̬��������塣һ��RenderModel���԰���
        // һ�������������ÿ������������Լ���MaterialID������ID����RenderTechnique������
        KlayGE::RenderModelPtr model = KlayGE::MakeSharedPtr<KlayGE::RenderModel>(L"model", KlayGE::SceneNode::SOA_Cullable);
        std::vector<KlayGE::StaticMeshPtr> meshes(2);
        std::vector<KlayGE::uint16_t> indices1;
        std::vector<KlayGE::uint16_t> indices2;

        indices1.push_back(0); indices1.push_back(4); indices1.push_back(1); indices1.push_back(5);
        indices1.push_back(2); indices1.push_back(6); indices1.push_back(3); indices1.push_back(7);
        indices1.push_back(0); indices1.push_back(4);;

        // ����������Ĳ�������
        meshes[0] = KlayGE::MakeSharedPtr<RenderPolygon>(L"side_mesh");
        meshes[0]->NumLods(1);
        // ���������ݵĵ�ַ�ʹ�С���ݸ�������󣬲�ָ��Ԫ�����ͣ��Լ�D3D11�µ����ݷ��ʲ���
       // �����Ԫ������vertex_element������������ɣ�
       // ��һ��VEU_Position�������������ͣ����˶�������֮�⣬������Ϊ����VEU_Normal����������VEU_TextureCoord�ȵ�
       // �ڶ�������Ϊ����ֵ�����������������ԣ�����ʾ�����������Ӧ������ͨ��
       // ������������ʾ���ݵ����ͣ�����EF_GR32F��float2����EF_BGR32F��float3����EF_ABGR32F��float4����

        meshes[0]->AddVertexStream(0,&vertices[0],static_cast<KlayGE::uint32_t>(sizeof(vertices[0])*vertices.size()),
            KlayGE::VertexElement(KlayGE::VEU_Position, 0, KlayGE::EF_BGR32F), KlayGE::EAH_GPU_Read);

        // ���������ݵĵ�ַ�ʹ�С���ݸ�������󣬴��⻹���������ݵ����ͣ�EF_R16UI��ʾ16λ�޷��������������ݷ��ʲ���
        meshes[0]->AddIndexStream(0, &indices1[0], static_cast<KlayGE::uint32_t>(sizeof(indices1[0]) * indices1.size()),
            KlayGE::EF_R16UI, KlayGE::EAH_GPU_Read);

        // ����ͼԪ�Ļ��Ʒ�ʽ������������������������ȡ�����������ķ������б��
        meshes[0]->GetRenderLayout().TopologyType(KlayGE::RenderLayout::TT_TriangleStrip);
        meshes[0]->PosBound(KlayGE::AABBox(KlayGE::float3(-1, -1, -1), KlayGE::float3(1, 1, 1)));

        indices2.push_back(0); indices2.push_back(1); indices2.push_back(2);
        indices2.push_back(0); indices2.push_back(2); indices2.push_back(3);
        indices2.push_back(7); indices2.push_back(6); indices2.push_back(5);
        indices2.push_back(7); indices2.push_back(5); indices2.push_back(4);

        // �ײ��Ͷ�������
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
        // �����е�������󴫵ݸ�RenderModel����ģ��
        model->AssignMeshes(meshes.begin(), meshes.end());
        model->BuildModelInfo();
        renderableMesh_ = model->RootNode();
      
        //������ģ�ʹ��ݸ��������󣬼��뵽��������
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

        // �����е�������󴫵ݸ�RenderModel����ģ��
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
    // ����ǰ��FPS��Ϣ������ַ����У��Ա���Ⱦ����Ļ��
    std::wostringstream stream;
    stream.precision(2);
    stream << std::fixed << this->FPS() << " FPS";

    // ʹ��֮ǰ����������������Ⱦ�ı���Ϣ��RenderText()���Խ��ܵĲ���������
    // X��Yλ�ã�KlayGE::Color��ɫ��std::wstring���͵��ַ������Լ������С
    font_->RenderText(0, 0, KlayGE::Color(1, 1, 0, 1), L"�Զ���������", 16);
    font_->RenderText(0, 18, KlayGE::Color(1, 1, 0, 1), stream.str(), 16);
}

KlayGE::uint32_t TutorFramework::DoUpdate(KlayGE::uint32_t pass)
{
    // ��ȡ��Ⱦ������󡣸���KlayGE.cfg�ļ����������ݣ�������ͨ��OpenGL����D3D11��ʵ��
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
