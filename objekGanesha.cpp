#include "objekGanesha.h"

void drawGaneshaBlock(float sx, float sy, float sz) {
    glBegin(GL_QUADS);
        // Depan
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-sx/2, -sy/2,  sz/2); glVertex3f( sx/2, -sy/2,  sz/2);
        glVertex3f( sx/2,  sy/2,  sz/2); glVertex3f(-sx/2,  sy/2,  sz/2);
        // Belakang
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-sx/2, -sy/2, -sz/2); glVertex3f(-sx/2,  sy/2, -sz/2);
        glVertex3f( sx/2,  sy/2, -sz/2); glVertex3f( sx/2, -sy/2, -sz/2);
        // Atas
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-sx/2,  sy/2, -sz/2); glVertex3f(-sx/2,  sy/2,  sz/2);
        glVertex3f( sx/2,  sy/2,  sz/2); glVertex3f( sx/2,  sy/2, -sz/2);
        // Bawah
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-sx/2, -sy/2, -sz/2); glVertex3f( sx/2, -sy/2, -sz/2);
        glVertex3f( sx/2, -sy/2,  sz/2); glVertex3f(-sx/2, -sy/2,  sz/2);
        // Kanan
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f( sx/2, -sy/2, -sz/2); glVertex3f( sx/2,  sy/2, -sz/2);
        glVertex3f( sx/2,  sy/2,  sz/2); glVertex3f( sx/2, -sy/2,  sz/2);
        // Kiri
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-sx/2, -sy/2, -sz/2); glVertex3f(-sx/2, -sy/2,  sz/2);
        glVertex3f(-sx/2,  sy/2,  sz/2); glVertex3f(-sx/2,  sy/2, -sz/2);
    glEnd();
}

void drawObjectGanesha() {
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
        // 0. Balok Putih (alas seperti meja)
        glColor3f(1.0f, 1.0f, 1.0f); // putih
        glPushMatrix();
            glTranslatef(0.0f, -1.6f, 0.0f);
            drawGaneshaBlock(6.0f, 0.6f, 6.0f);
        glPopMatrix();

        // 1. Tatakan Abu-abu di atas balok putih
        glColor3f(0.5f, 0.5f, 0.5f);
        glPushMatrix();
            glTranslatef(0.0f, -1.0f, 0.0f);
            drawGaneshaBlock(5.0f, 0.5f, 5.0f);
            glTranslatef(0.0f, 0.4f, 0.0f);
            drawGaneshaBlock(4.0f, 0.4f, 4.0f);
        glPopMatrix();

        // 2. Badan
        glColor3f(0.6f, 0.6f, 0.6f);
        glPushMatrix();
            glTranslatef(0.0f, 0.7f, 0.0f);
            drawGaneshaBlock(2.2f, 2.0f, 2.0f);
        glPopMatrix();

        // 3. Kepala & Mahkota
        glColor3f(0.65f, 0.65f, 0.65f);
        glPushMatrix();
            glTranslatef(0.0f, 2.2f, 0.0f);
            drawGaneshaBlock(1.4f, 1.2f, 1.4f);
            // Telinga
            glPushMatrix(); glTranslatef(1.0f, 0.1f, 0.0f); drawGaneshaBlock(0.4f, 0.8f, 0.6f); glPopMatrix();
            glPushMatrix(); glTranslatef(-1.0f, 0.1f, 0.0f); drawGaneshaBlock(0.4f, 0.8f, 0.6f); glPopMatrix();
            // Mahkota
            glColor3f(0.8f, 0.8f, 0.8f);
            glTranslatef(0.0f, 0.9f, 0.0f); drawGaneshaBlock(1.0f, 0.8f, 1.0f);
            glTranslatef(0.0f, 0.5f, 0.0f); drawGaneshaBlock(0.6f, 0.4f, 0.6f);
        glPopMatrix();

        // 4. Belalai
        glColor3f(0.6f, 0.6f, 0.6f);
        glPushMatrix();
            glTranslatef(0.0f, 2.0f, 0.7f); drawGaneshaBlock(0.4f, 0.4f, 0.6f);
            glTranslatef(0.0f, -0.4f, 0.4f); drawGaneshaBlock(0.4f, 0.6f, 0.4f);
            glTranslatef(0.2f, -0.3f, 0.2f); drawGaneshaBlock(0.5f, 0.3f, 0.4f);
            glTranslatef(0.2f, -0.2f, 0.2f); drawGaneshaBlock(0.4f, 0.3f, 0.3f);
        glPopMatrix();

        // 5. Lengan
        glColor3f(0.6f, 0.6f, 0.6f);
        glPushMatrix(); glTranslatef(1.3f, 1.0f, 0.4f); drawGaneshaBlock(0.4f, 0.4f, 1.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(-1.3f, 1.0f, 0.4f); drawGaneshaBlock(0.4f, 0.4f, 1.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(1.4f, 1.5f, -0.4f); drawGaneshaBlock(0.4f, 0.8f, 0.4f); glPopMatrix();
        glPushMatrix(); glTranslatef(-1.4f, 1.5f, -0.4f); drawGaneshaBlock(0.4f, 0.8f, 0.4f); glPopMatrix();

        // 6. Kaki Bersila
        glPushMatrix(); glTranslatef(0.9f, -0.2f, 0.5f); drawGaneshaBlock(1.4f, 0.6f, 1.0f); glPopMatrix();
        glPushMatrix(); glTranslatef(-0.9f, -0.2f, 0.5f); drawGaneshaBlock(1.4f, 0.6f, 1.0f); glPopMatrix();

    glPopMatrix();
}
