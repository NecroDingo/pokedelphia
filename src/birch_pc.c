#include "global.h"
#include "event_data.h"
#include "field_message_box.h"
#include "pokedex.h"
#include "strings.h"

bool16 ScriptGetPokedexInfo(void)
{
    if (gSpecialVar_0x8004 == 0) // is national dex not present?
    {
        gSpecialVar_0x8005 = GetHoennPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetHoennPokedexCount(FLAG_GET_CAUGHT);
    }
    else
    {
        gSpecialVar_0x8005 = GetNationalPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetNationalPokedexCount(FLAG_GET_CAUGHT);
    }

    return IsNationalPokedexEnabled();
}

#define FRANK_DEX_STRINGS 21

static const u8 *const sFrankDexRatingTexts[FRANK_DEX_STRINGS] =
{
    gFrankDexRatingText_LessThan10,
    gFrankDexRatingText_LessThan20,
    gFrankDexRatingText_LessThan30,
    gFrankDexRatingText_LessThan40,
    gFrankDexRatingText_LessThan50,
    gFrankDexRatingText_LessThan60,
    gFrankDexRatingText_LessThan70,
    gFrankDexRatingText_LessThan80,
    gFrankDexRatingText_LessThan90,
    gFrankDexRatingText_LessThan100,
    gFrankDexRatingText_LessThan110,
    gFrankDexRatingText_LessThan120,
    gFrankDexRatingText_LessThan130,
    gFrankDexRatingText_LessThan140,
    gFrankDexRatingText_LessThan150,
    gFrankDexRatingText_LessThan160,
    gFrankDexRatingText_LessThan170,
    gFrankDexRatingText_LessThan180,
    gFrankDexRatingText_LessThan190,
    gFrankDexRatingText_LessThan200,
    gFrankDexRatingText_DexCompleted,
};

// This shows your Hoenn Pokédex rating and not your National Dex.
const u8 *GetPokedexRatingText(u32 count)
{
    u32 i, j;
    u16 maxDex = HOENN_DEX_COUNT - 1;
    // doesNotCountForRegionalPokedex
    for(i = 0; i < HOENN_DEX_COUNT; i++)
    {
        j = NationalPokedexNumToSpecies(HoennToNationalOrder(i + 1));
        if (gSpeciesInfo[j].isMythical && !gSpeciesInfo[j].dexForceRequired)
        {
            if (GetSetPokedexFlag(j, FLAG_GET_CAUGHT))
                count--;
            maxDex--;
        }
    }
    return sFrankDexRatingTexts[(count * (FRANK_DEX_STRINGS - 1)) / maxDex];
}

void ShowPokedexRatingMessage(void)
{
    ShowFieldMessage(GetPokedexRatingText(gSpecialVar_0x8004));
}
