#pragma once
#include	<assimp/Importer.hpp>
#include	<assimp/scene.h>
#include	<assimp/postprocess.h>
#include	<assimp/cimport.h>

namespace AssimpPerse
{
	struct VERTEX {
		std::string meshname;		// ���b�V����
		aiVector3D	pos;			// �ʒu
		aiVector3D	normal;			// �@��
		aiColor4D	color;			// ���_�J���[	
		aiVector3D	texcoord;		// �e�N�X�`�����W	
		int			materialindex;	// �}�e���A���C���f�b�N�X
		std::string mtrlname;		// �}�e���A����
	};

	struct SUBSET {
		std::string meshname;		// ���b�V����
		int materialindex;			// �}�e���A���C���f�b�N�X
		unsigned int VertexBase;	// ���_�o�b�t�@�̃x�[�X
		unsigned int VertexNum;		// ���_��
		unsigned int IndexBase;		// �C���f�b�N�X�o�b�t�@�̃x�[�X
		unsigned int IndexNum;		// �C���f�b�N�X��
		std::string	 mtrlname;		// �}�e���A����
	};

	struct MATERIAL {
		std::string mtrlname;		// �}�e���A����
		aiColor4D	Ambient;		// �A���r�G���g
		aiColor4D	Diffuse;		// �f�B�t���[�Y
		aiColor4D	Specular;		// �X�y�L����
		aiColor4D	Emission;		// �G�~�b�V����
		float		Shiness;		// �V���C�l�X
		std::string texturename;	// �e�N�X�`����
	};

	void GetModelData(std::string filename, std::string texturedirectory);
	std::vector<SUBSET> GetSubsets();
	std::vector<std::vector<VERTEX>> GetVertices();
	std::vector<std::vector<unsigned int>> GetIndices();
	std::vector<MATERIAL> GetMaterials();
	std::vector<std::unique_ptr<Texture>> GetTextures();
}
