
/*{{BLOCK(bg_forest)                                                    */

/*======================================================================*/
/*                                                                      */
/* bg_forest, 512x256@4,                                                */
/* Transparent palette entry: 0.                                        */
/* + palette 16 entries, not compressed                                 */
/* + 9 tiles (t|f|p reduced) not compressed                             */
/* + regular map (in SBBs), not compressed, 64x32                       */
/* Total size: 32 + 288 + 4096 = 4416                                   */
/*                                                                      */
/* Time-stamp: 2012-07-22, 14:15:50                                     */
/* Exported by Cearn's GBA Image Transmogrifier                         */
/* ( http://www.coranac.com/projects/#grit )                            */
/*                                                                      */
/*======================================================================*/

#ifndef GRIT_BG_FOREST_H
#define GRIT_BG_FOREST_H

#define bg_forestTilesLen 288
extern const unsigned short bg_forestTiles[144];

#define bg_forestMapLen 4096
extern const unsigned short bg_forestMap[2048];

#define bg_forestPalLen 32
extern const unsigned short bg_forestPal[16];

#endif /* GRIT_BG_FOREST_H                                              */

/*}}BLOCK(bg_forest)                                                    */
