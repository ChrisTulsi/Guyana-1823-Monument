// store current OpenGL state
glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT | GL_STENCIL_BUFFER_BIT);

// draw the model with the light disabled
glDisable(/* light handle */);
model.draw();
glEnable(/* light handle */);

// store current OpenGL state
glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_POLYGON_BIT | GL_STENCIL_BUFFER_BIT);

glColorMask(0, 0, 0, 0); // do not write to the color buffer
glDepthMask(0); // do not write to the depth (Z) buffer
glEnable(GL_CULL_FACE); // cull faces (back or front)
glEnable(GL_STENCIL_TEST); // enable stencil testing

// set the reference stencil value to 0
glStencilFunc(GL_ALWAYS, 0, ~0);

// increment the stencil value on Z fail
glStencilOp(GL_KEEP, GL_INCR, GL_KEEP);

// draw only the back faces of the shadow volume
glCullFace(GL_FRONT);
model.drawShadowVolume(light);

// decrement the stencil value on Z fail
glStencilOp(GL_KEEP, GL_DECR, GL_KEEP);

// draw only the front faces of the shadow volume
glCullFace(GL_BACK);
model.drawShadowVolume(light);

// restore OpenGL state
glPopAttrib();

// re-draw the model with the light enabled only where
// it has previously been drawn
glDepthFunc(GL_EQUAL);

// update the color only where the stencil value is 0
glEnable(GL_STENCIL_TEST);
glStencilFunc(GL_EQUAL, 0, ~0);
glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

model.draw();

// restore OpenGL state
glPopAttrib();
