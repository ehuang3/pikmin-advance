
/*{{BLOCK(bd_forest)                                                    */

/*======================================================================*/
/*                                                                      */
/* bd_forest, 256x256@4,                                                */
/* Transparent palette entry: 0.                                        */
/* + palette 16 entries, not compressed                                 */
/* + 13 tiles (t|f|p reduced) not compressed                            */
/* + regular map (in SBBs), not compressed, 32x32                       */
/* Total size: 32 + 416 + 2048 = 2496                                   */
/*                                                                      */
/* Time-stamp: 2012-07-22, 14:02:06                                     */
/* Exported by Cearn's GBA Image Transmogrifier                         */
/* ( http://www.coranac.com/projects/#grit )                            */
/*                                                                      */
/*======================================================================*/

#ifndef GRIT_BD_FOREST_H
#define GRIT_BD_FOREST_H

#define bd_forestTilesLen 416
extern const unsigned short bd_forestTiles[208];

#define bd_forestMapLen 2048
extern const unsigned short bd_forestMap[1024];

#define bd_forestPalLen 32
extern const unsigned short bd_forestPal[16];

#endif /* GRIT_BD_FOREST_H                                              */

/*}}BLOCK(bd_forest)                                                    */
