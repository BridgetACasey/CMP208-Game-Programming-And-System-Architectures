#include "game_object.h"

//
// UpdateFromSimulation
// 
// Update the transform of this object from a physics rigid body
//

void GameObject::BuildTransform()
{
	gef::Matrix44 final_, trans, rotX, rotY, rotZ, scale_;

	scale_.Scale(scale);

	rotX.RotationX(rotation.x());
	rotY.RotationX(rotation.y());
	rotZ.RotationX(rotation.z());

	trans.SetIdentity();
	trans.SetTranslation(position);

	final_ = scale_ * rotX * rotY * rotZ * trans;

	set_transform(final_);
}
