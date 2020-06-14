#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void showFace(string tag, FT_Bitmap *bm)
{
    Mat face_mat(bm->rows, bm->width, CV_8UC1);
    for (size_t r = 0; r < bm->rows; r++)
    {
        for (size_t c = 0; c < bm->width; c++)
        {
            face_mat.at<uchar>(r, c) = bm->buffer[r * bm->width + c];
        }
    }

    imshow(tag, face_mat);
}

int main()
{
    FT_Library library; /* handle to library     */
    FT_Face face;       /* handle to face object */
    FT_Error error;

    // init freetype library
    error = FT_Init_FreeType(&library);
    if (error)
    {
        cerr << "Freetype init fail, code is: " << error << endl;
        return error;
    }
    else
    {
        cout << "Freetype init success." << endl;
    }

    // load a font face
    error = FT_New_Face(library, "/home/suika/VsCodeProjects/FreeTypeDemo/font.ttf", 0, &face);
    if (error == FT_Err_Unknown_File_Format)
    {
        cerr << "the font file could be opened and read, but it appears that its font format is unsupported" << endl;
        return error;
    }
    else if (error)
    {
        cerr << "can not open font file. error code is: " << error << endl;
        return error;
    }

    // set char size
    error = FT_Set_Char_Size(face, 0, 16 * 64, 300, 300);

    // simple text rendering
    FT_GlyphSlot slot = face->glyph; /* a small shortcut */
    int pen_x, pen_y, n;

    pen_x = 300;
    pen_y = 200;
    const int num_chars = 8;
    const int texts[] = {0x40, 0x41, 0x42, 0x43, 0x44, 0x4B, 0x45, 0x3F};
    const char *textArr2 = "suika jy";

    for (n = 0; n < num_chars; n++)
    {
        FT_UInt glyph_index;

        glyph_index = FT_Get_Char_Index(face, texts[n]);

        error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
        if (error)
            continue;

        error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
        if (error)
            continue;

        showFace("[img]" + n, &slot->bitmap);
    }

    waitKey(0);
    destroyAllWindows();
    return 0;
}