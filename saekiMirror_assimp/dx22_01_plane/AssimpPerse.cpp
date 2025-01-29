#include	<vector>
#include	<iostream>
#include	<unordered_map>
#include	<cassert>
#include	"Texture.h"
#include	"AssimpPerse.h"

#pragma comment(lib, "assimp-vc143-mtd.lib")

namespace AssimpPerse
{
	std::vector<std::vector<VERTEX>> g_vertices{};		// ���_�f�[�^�i���b�V���P�ʁj
	std::vector<std::vector<unsigned int>> g_indices{};	// �C���f�b�N�X�f�[�^�i���b�V���P�ʁj
	std::vector<SUBSET> g_subsets{};					// �T�u�Z�b�g���
	std::vector<MATERIAL> g_materials{};				// �}�e���A��
	std::vector<std::unique_ptr<Texture>> g_textures;	// �f�B�t���[�Y�e�N�X�`���Q

	// �f�B�t���[�YTxture�R���e�i��Ԃ�
	std::vector<std::unique_ptr<Texture>> GetTextures()
	{
		return std::move(g_textures);
	}

	// �}�e���A������assimp���g�p���Ď擾����
	void GetMaterialData(const aiScene* pScene, std::string texturedirectory)
	{
		// �}�e���A�������e�N�X�`���i�[�G���A��p�ӂ���
		g_textures.resize(pScene->mNumMaterials);

		// �}�e���A���������[�v
		for (unsigned int m = 0; m < pScene->mNumMaterials; m++)
		{
			aiMaterial* material = pScene->mMaterials[m];

			// �}�e���A�����擾
			std::string mtrlname = std::string(material->GetName().C_Str());
			std::cout << mtrlname << std::endl;

			// �}�e���A�����
			aiColor4D ambient;
			aiColor4D diffuse;
			aiColor4D specular;
			aiColor4D emission;
			float shiness;

			// �A���r�G���g
			if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient)) {
			}
			else {
				ambient = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
			}

			// �f�B�t���[�Y
			if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse)) {
			}
			else {
				diffuse = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
			}

			// �X�y�L����
			if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular)) {
			}
			else {
				specular = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
			}

			// �G�~�b�V����
			if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emission)) {
			}
			else {
				emission = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
			}

			// �V���C�l�X
			if (AI_SUCCESS == aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shiness)) {
			}
			else {
				shiness = 0.0f;
			}

			// ���̃}�e���A���ɕR�Â��Ă���f�B�t���[�Y�e�N�X�`���������[�v
			std::vector<std::string> texpaths{};

			for (unsigned int t = 0; t < material->GetTextureCount(aiTextureType_DIFFUSE); t++)
			{
				aiString path{};

				// t�Ԗڂ̃e�N�X�`���p�X�擾
				if (AI_SUCCESS == material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, t), path))
				{
					// �e�N�X�`���p�X�擾
					std::string texpath = std::string(path.C_Str());
					std::cout << texpath << std::endl;

					texpaths.push_back(texpath);
					// �����e�N�X�`�����ǂ����𔻒f����
					if (auto tex = pScene->GetEmbeddedTexture(path.C_Str())) {

						std::unique_ptr<Texture> texture = std::make_unique<Texture>();

						// �����e�N�X�`���̏ꍇ
						bool sts = texture->LoadFromFemory(
							(unsigned char*)tex->pcData,			// �擪�A�h���X
							tex->mWidth);			// �e�N�X�`���T�C�Y�i�������ɂ���ꍇ�����T�C�Y�j	
						if (sts) {
							g_textures[m] = std::move(texture);
						}
						std::cout << "Embedded" << std::endl;

					}
					else {
						// �O���e�N�X�`���t�@�C���̏ꍇ
						std::unique_ptr<Texture> texture;
						texture = std::make_unique<Texture>();

						std::string texname = texturedirectory + "/" + texpath;

						bool sts = texture->Load(texname);
						if (sts) {
							g_textures[m] = std::move(texture);
						}

						std::cout << "other Embedded" << std::endl;
					}
				}
				// �f�B�t���[�Y�e�N�X�`�����Ȃ������ꍇ
				else
				{
					// �O���e�N�X�`���t�@�C���̏ꍇ
					std::unique_ptr<Texture> texture;
					texture = std::make_unique<Texture>();
					g_textures[m] = std::move(texture);
				}
			}

			// �}�e���A������ۑ�
			AssimpPerse::MATERIAL mtrl{};
			mtrl.mtrlname = mtrlname;
			mtrl.Ambient = ambient;
			mtrl.Diffuse = diffuse;
			mtrl.Specular = specular;
			mtrl.Emission = emission;
			mtrl.Shiness = shiness;
			if (texpaths.size() == 0)
			{
				mtrl.texturename = "";
			}
			else
			{
				mtrl.texturename = texpaths[0];
			}
			g_materials.push_back(mtrl);
		}
	}

	void GetModelData(std::string filename, std::string texturedirectory)
	{
		// �V�[�����\�z
		Assimp::Importer importer;

		// �V�[�������\�z
		const aiScene* pScene = importer.ReadFile(
			filename.c_str(),
			aiProcess_ConvertToLeftHanded |	// ������W�n�ɕϊ�����
			aiProcess_Triangulate);			// �O�p�`������

		if (pScene == nullptr)
		{
			std::cout << "load error" << filename.c_str() << importer.GetErrorString() << std::endl;
		}
		assert(pScene != nullptr);

		// �}�e���A�����擾
		GetMaterialData(pScene, texturedirectory);

		// ���b�V���������[�v�i�}�e���A�����Ƀ��b�V���𕪊�����悤�Ɏw�肵�Ă���j
		g_vertices.resize(pScene->mNumMeshes);

		for (unsigned int m = 0; m < pScene->mNumMeshes; m++)
		{
			aiMesh* mesh = pScene->mMeshes[m];

			// ���b�V�����擾
			std::string meshname = std::string(mesh->mName.C_Str());

			//�@���_�������[�v
			for (unsigned int vidx = 0; vidx < mesh->mNumVertices; vidx++)
			{
				// ���_�f�[�^
				VERTEX	v{};
				v.meshname = meshname;		// ���b�V�����Z�b�g

				// ���W		
				v.pos = mesh->mVertices[vidx];

				// ���̒��_���g�p���Ă���}�e���A���̃C���f�b�N�X�ԍ��i���b�V�����́j
				// ���g�p���ă}�e���A�������Z�b�g
				v.materialindex = mesh->mMaterialIndex;

				v.mtrlname = g_materials[mesh->mMaterialIndex].mtrlname;

				// �@������H
				if (mesh->HasNormals()) {
					v.normal = mesh->mNormals[vidx];
				}
				else
				{
					v.normal = aiVector3D(0.0f, 0.0f, 0.0f);
				}

				// ���_�J���[�H�i�O�Ԗځj
				if (mesh->HasVertexColors(0)) {
					v.color = mesh->mColors[0][vidx];
				}
				else
				{
					v.color = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
				}

				// �e�N�X�`������H�i�O�Ԗځj
				if (mesh->HasTextureCoords(0)) {
					v.texcoord = mesh->mTextureCoords[0][vidx];
				}
				else
				{
					v.texcoord = aiVector3D(0.0f, 0.0f, 0.0f);
				}

				// ���_�f�[�^��ǉ�
				g_vertices[m].push_back(v);
			}
		}

		// ���b�V���������[�v
		// �C���f�b�N�X�f�[�^�쐬
		g_indices.resize(pScene->mNumMeshes);
		for (unsigned int m = 0; m < pScene->mNumMeshes; m++)
		{
			aiMesh* mesh = pScene->mMeshes[m];

			// ���b�V�����擾
			std::string meshname = std::string(mesh->mName.C_Str());

			// �C���f�b�N�X�������[�v
			for (unsigned int fidx = 0; fidx < mesh->mNumFaces; fidx++)
			{
				aiFace face = mesh->mFaces[fidx];

				assert(face.mNumIndices == 3);	// �O�p�`�̂ݑΉ�

				// �C���f�b�N�X�f�[�^��ǉ�
				for (unsigned int i = 0; i < face.mNumIndices; i++)
				{
					g_indices[m].push_back(face.mIndices[i]);
				}
			}
		}

		// �T�u�Z�b�g���𐶐�
		g_subsets.resize(pScene->mNumMeshes);
		for (unsigned int m = 0; m < g_subsets.size(); m++)
		{
			g_subsets[m].IndexNum = (unsigned int)g_indices[m].size();
			g_subsets[m].VertexNum = (unsigned int)g_vertices[m].size();
			g_subsets[m].VertexBase = 0;
			g_subsets[m].IndexBase = 0;
			g_subsets[m].meshname = g_vertices[m][0].meshname;
			g_subsets[m].mtrlname = g_vertices[m][0].mtrlname;
			g_subsets[m].materialindex = g_vertices[m][0].materialindex;
		}

		// �T�u�Z�b�g���𑊑ΓI�Ȃ��̂ɂ���	
		for (int m = 0; m < g_subsets.size(); m++)
		{
			// ���_�o�b�t�@�̃x�[�X���v�Z
			g_subsets[m].VertexBase = 0;
			for (int i = m - 1; i >= 0; i--) {
				g_subsets[m].VertexBase += g_subsets[i].VertexNum;
			}

			// �C���f�b�N�X�o�b�t�@�̃x�[�X���v�Z
			g_subsets[m].IndexBase = 0;
			for (int i = m - 1; i >= 0; i--) {
				g_subsets[m].IndexBase += g_subsets[i].IndexNum;
			}
		}
	}

	// �T�u�Z�b�g���
	std::vector<SUBSET> GetSubsets()
	{
		return g_subsets;
	}

	std::vector<std::vector<VERTEX>> GetVertices()
	{
		return g_vertices; // ���_�f�[�^�i���b�V���P�ʁj
	}

	std::vector<std::vector<unsigned int>> GetIndices()
	{
		return g_indices; // �C���f�b�N�X�f�[�^�i���b�V���P�ʁj
	}

	std::vector<MATERIAL> GetMaterials()
	{
		return g_materials; // �}�e���A��
	}
}
