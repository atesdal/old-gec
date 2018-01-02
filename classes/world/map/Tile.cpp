#include "Tile.hpp"
#include "Feature.hpp"
#include "Resource.hpp"
#include "..\..\graphics\Graphics.hpp"
#include "..\..\utils\Utilities.hpp"
#include "..\..\utils\Camera.hpp"

namespace MAP
{
	Tile::Tile(std::string spriteKey, int foodYield, int prodYield) :
		spriteKey_(spriteKey), food_(foodYield), prod_(prodYield), isImproved_(false), feature_(nullptr), resource_(nullptr)
	{
		tileBounds_.north = nullptr;
		tileBounds_.south = nullptr;
		tileBounds_.east = nullptr;
		tileBounds_.west = nullptr;
	}


	Tile::~Tile()
	{

	}

	void Tile::Update()
	{
		if (feature_ != nullptr) {

		}
		if (resource_ != nullptr) {
			//Add yield bonus (if any)
			if (isImproved_) {
				//Add resource to owner
			}
		}
		if (isImproved_) {
			//Add +1 to yields
		}
	}

	void Tile::Render(GFX::Graphics *gfx, Util::Camera *pCamera, const int screenWidth, const int screenHeight) const
	{
		float camX = pos_.x + float(pCamera->Get_X());
		float camY = pos_.y + float(pCamera->Get_Y());
		Util::Vector2 renderPos(camX, camY);

		gfx->Draw_Sprite(spriteKey_, renderPos);
		if (feature_ != nullptr) {
			gfx->Draw_Sprite(feature_->Get_Sprite_Key(), renderPos);
		}
		if (resource_ != nullptr) {
			gfx->Draw_Sprite(resource_->Get_Sprite_Key(), renderPos);
		}
		//Need to check if tile is on screen before rendering text, huge performance hit on large maps
		if ((int(renderPos.x) >= 0 && int(renderPos.y) >= 0) && (int(renderPos.x) < screenWidth && int(renderPos.y) < screenHeight)) {
			//HAPI.RenderText(int(renderPos.x + 6), int(renderPos.y + 5), HAPI_TColour::WHITE, Util::To_String(food_));
			//HAPI.RenderText(int(renderPos.x + 5), int(renderPos.y + 15), HAPI_TColour::WHITE, Util::To_String(prod_));
		}

	}

	bool Tile::Add_Feature(MAP::Feature *feature)
	{
		//Checks that input feature is not nullptr
		if (feature == nullptr) {
			return false;
		}
		//Checks if feature already exists
		if (feature_ != nullptr) {
			return false;
		}
		feature_ = feature;
		food_ += feature_->Get_F_Bonus();
		prod_ += feature_->Get_P_Bonus();
		return true;
	}

	bool Tile::Delete_Feature()
	{
		if (feature_ == nullptr) {
			return false;
		}
		//Add feature_->Get_F_Harvest() and feature_->Get_P_Harvest() to owner of tile
		feature_ = nullptr;
		return true;
	}

	bool Tile::Add_Resource(Resource *resource)
	{
		//Checks that input feature is not nullptr
		if (resource == nullptr) {
			return false;
		}
		//Checks if feature already exists
		if (resource_ != nullptr) {
			return false;
		}
		resource_ = resource;
		food_ += resource_->Get_F_Bonus();
		prod_ += resource_->Get_P_Bonus();
		//Add unique resource when this is implemented
		return true;
	}

	bool Tile::Delete_Resource()
	{
		if (resource_ == nullptr) {
			return false;
		}
		//Add resource_->Get_F_Harvest() and resource_->Get_P_Harvest() to owner of tile
		//And also remove unique resource tile
		feature_ = nullptr;
		return true;
	}
}
