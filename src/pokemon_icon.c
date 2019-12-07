#include "global.h"
#include "graphics.h"
#include "mail.h"
#include "palette.h"
#include "pokemon_icon.h"
#include "sprite.h"
#include "constants/species.h"

#define POKE_ICON_BASE_PAL_TAG 56000

struct MonIconSpriteTemplate
{
    const struct OamData *oam;
    const u8 *image;
    const union AnimCmd *const *anims;
    const union AffineAnimCmd *const *affineAnims;
    void (*callback)(struct Sprite *);
    u16 paletteTag;
};

// static functions
static u8 CreateMonIconSprite(struct MonIconSpriteTemplate *, s16, s16, u8);

// .rodata

const u8 *const gMonIconTable[] =
{
    [SPECIES_NONE] = gMonIcon_Bulbasaur,
    [SPECIES_BULBASAUR] = gMonIcon_Bulbasaur,
    [SPECIES_IVYSAUR] = gMonIcon_Ivysaur,
    [SPECIES_VENUSAUR] = gMonIcon_Venusaur,
    [SPECIES_CHARMANDER] = gMonIcon_Charmander,
    [SPECIES_CHARMELEON] = gMonIcon_Charmeleon,
    [SPECIES_CHARIZARD] = gMonIcon_Charizard,
    [SPECIES_SQUIRTLE] = gMonIcon_Squirtle,
    [SPECIES_WARTORTLE] = gMonIcon_Wartortle,
    [SPECIES_BLASTOISE] = gMonIcon_Blastoise,
    [SPECIES_SNIVY] = gMonIcon_Caterpie,
    [SPECIES_SERVINE] = gMonIcon_Metapod,
    [SPECIES_SERPERIOR] = gMonIcon_Butterfree,
    [SPECIES_WEEDLE] = gMonIcon_Weedle,
    [SPECIES_KAKUNA] = gMonIcon_Kakuna,
    [SPECIES_BEEDRILL] = gMonIcon_Beedrill,
    [SPECIES_PIDGEY] = gMonIcon_Pidgey,
    [SPECIES_PIDGEOTTO] = gMonIcon_Pidgeotto,
    [SPECIES_PIDGEOT] = gMonIcon_Pidgeot,
    [SPECIES_RATTATA] = gMonIcon_Rattata,
    [SPECIES_RATICATE] = gMonIcon_Raticate,
    [SPECIES_NOIBAT] = gMonIcon_Spearow,
    [SPECIES_NOIVERN] = gMonIcon_Fearow,
    [SPECIES_EKANS] = gMonIcon_Ekans,
    [SPECIES_ARBOK] = gMonIcon_Arbok,
    [SPECIES_PIKACHU] = gMonIcon_Pikachu,
    [SPECIES_RAICHU] = gMonIcon_Raichu,
    [SPECIES_SANDSHREW] = gMonIcon_Sandshrew,
    [SPECIES_SANDSLASH] = gMonIcon_Sandslash,
    [SPECIES_NIDORAN_F] = gMonIcon_NidoranF,
    [SPECIES_NIDORINA] = gMonIcon_Nidorina,
    [SPECIES_NIDOQUEEN] = gMonIcon_Nidoqueen,
    [SPECIES_NIDORAN_M] = gMonIcon_NidoranM,
    [SPECIES_NIDORINO] = gMonIcon_Nidorino,
    [SPECIES_NIDOKING] = gMonIcon_Nidoking,
    [SPECIES_CLEFAIRY] = gMonIcon_Clefairy,
    [SPECIES_CLEFABLE] = gMonIcon_Clefable,
    [SPECIES_VULPIX] = gMonIcon_Vulpix,
    [SPECIES_NINETALES] = gMonIcon_Ninetales,
    [SPECIES_FROAKIE] = gMonIcon_Jigglypuff,
    [SPECIES_FROGADIER] = gMonIcon_Wigglytuff,
    [SPECIES_GRENINJA] = gMonIcon_Zubat,
    [SPECIES_DURANT] = gMonIcon_Golbat,
    [SPECIES_ROWLET] = gMonIcon_Oddish,
    [SPECIES_DARTRIX] = gMonIcon_Gloom,
    [SPECIES_DECIDUEYE] = gMonIcon_Vileplume,
    [SPECIES_BIDOOF] = gMonIcon_Paras,
    [SPECIES_BIBAREL] = gMonIcon_Parasect,
    [SPECIES_VENONAT] = gMonIcon_Venonat,
    [SPECIES_VENOMOTH] = gMonIcon_Venomoth,
    [SPECIES_KARRABLAST] = gMonIcon_Diglett,
    [SPECIES_ESCAVALIER] = gMonIcon_Dugtrio,
    [SPECIES_TYRUNT] = gMonIcon_Meowth,
    [SPECIES_TYRANTRUM] = gMonIcon_Persian,
    [SPECIES_PSYDUCK] = gMonIcon_Psyduck,
    [SPECIES_VESPIQUEEN] = gMonIcon_Golduck,
    [SPECIES_PURRLOIN] = gMonIcon_Mankey,
    [SPECIES_LIEPARD] = gMonIcon_Primeape,
    [SPECIES_GROWLITHE] = gMonIcon_Growlithe,
    [SPECIES_ARCANINE] = gMonIcon_Arcanine,
    [SPECIES_PIDOVE] = gMonIcon_Poliwag,
    [SPECIES_TRANQUILL] = gMonIcon_Poliwhirl,
    [SPECIES_UNFEZANT] = gMonIcon_Poliwrath,
    [SPECIES_ABRA] = gMonIcon_Abra,
    [SPECIES_KADABRA] = gMonIcon_Kadabra,
    [SPECIES_ALAKAZAM] = gMonIcon_Alakazam,
    [SPECIES_SCATTERBUG] = gMonIcon_Machop,
    [SPECIES_SPEWPA] = gMonIcon_Machoke,
    [SPECIES_VIVILLON] = gMonIcon_Machamp,
    [SPECIES_VENIPEDE] = gMonIcon_Bellsprout,
    [SPECIES_WHIRLIPEDE] = gMonIcon_Weepinbell,
    [SPECIES_SCOLIPEDE] = gMonIcon_Victreebel,
    [SPECIES_TENTACOOL] = gMonIcon_Tentacool,
    [SPECIES_TENTACRUEL] = gMonIcon_Tentacruel,
    [SPECIES_ESPURR] = gMonIcon_Geodude,
    [SPECIES_MEOWSTIC_M] = gMonIcon_Graveler,
    [SPECIES_MEOWSTIC_F] = gMonIcon_Golem,
    [SPECIES_PONYTA] = gMonIcon_Ponyta,
    [SPECIES_RAPIDASH] = gMonIcon_Rapidash,
    [SPECIES_VULLABY] = gMonIcon_Slowpoke,
    [SPECIES_MANDIBUZZ] = gMonIcon_Slowbro,
    [SPECIES_MAGNEMITE] = gMonIcon_Magnemite,
    [SPECIES_MAGNETON] = gMonIcon_Magneton,
    [SPECIES_MAGNEZONE] = gMonIcon_Farfetchd,
    [SPECIES_ROTOM] = gMonIcon_Doduo,
    [SPECIES_LILLIPUP] = gMonIcon_Dodrio,
    [SPECIES_HERDIER] = gMonIcon_Seel,
    [SPECIES_STOUTLAND] = gMonIcon_Dewgong,
    [SPECIES_MUDBRAY] = gMonIcon_Grimer,
    [SPECIES_MUDSDALE] = gMonIcon_Muk,
    [SPECIES_DUCKLETT] = gMonIcon_Shellder,
    [SPECIES_SWANNA] = gMonIcon_Cloyster,
    [SPECIES_GASTLY] = gMonIcon_Gastly,
    [SPECIES_HAUNTER] = gMonIcon_Haunter,
    [SPECIES_GENGAR] = gMonIcon_Gengar,
    [SPECIES_ONIX] = gMonIcon_Onix,
    [SPECIES_RUFFLET] = gMonIcon_Drowzee,
    [SPECIES_BRAVIARY] = gMonIcon_Hypno,
    [SPECIES_KRABBY] = gMonIcon_Krabby,
    [SPECIES_KINGLER] = gMonIcon_Kingler,
    [SPECIES_SCRAGGY] = gMonIcon_Voltorb,
    [SPECIES_SCRAFTY] = gMonIcon_Electrode,
    [SPECIES_CUBCHOO] = gMonIcon_Exeggcute,
    [SPECIES_BEARTIC] = gMonIcon_Exeggutor,
    [SPECIES_CUBONE] = gMonIcon_Cubone,
    [SPECIES_MAROWAK] = gMonIcon_Marowak,
    [SPECIES_HITMONLEE] = gMonIcon_Hitmonlee,
    [SPECIES_HITMONCHAN] = gMonIcon_Hitmonchan,
    [SPECIES_BUNNELBY] = gMonIcon_Lickitung,
    [SPECIES_DIGGERSBY] = gMonIcon_Koffing,
    [SPECIES_EMOLGA] = gMonIcon_Weezing,
    [SPECIES_RHYHORN] = gMonIcon_Rhyhorn,
    [SPECIES_RHYDON] = gMonIcon_Rhydon,
    [SPECIES_CHANSEY] = gMonIcon_Chansey,
    [SPECIES_TANGELA] = gMonIcon_Tangela,
    [SPECIES_TANGROWTH] = gMonIcon_Kangaskhan,
    [SPECIES_SCRAGGY] = gMonIcon_Horsea,
    [SPECIES_SCRAFTY] = gMonIcon_Seadra,
    [SPECIES_DRILBUR] = gMonIcon_Goldeen,
    [SPECIES_EXCADRILL] = gMonIcon_Seaking,
    [SPECIES_STARYU] = gMonIcon_Staryu,
    [SPECIES_STARMIE] = gMonIcon_Starmie,
    [SPECIES_PACHIRISU] = gMonIcon_Mrmime,
    [SPECIES_SCYTHER] = gMonIcon_Scyther,
    [SPECIES_LARVESTA] = gMonIcon_Jynx,
    [SPECIES_VOLCARONA] = gMonIcon_Electabuzz,
    [SPECIES_BUIZEL] = gMonIcon_Magmar,
    [SPECIES_PINSIR] = gMonIcon_Pinsir,
    [SPECIES_FLOATZEL] = gMonIcon_Tauros,
    [SPECIES_MAGIKARP] = gMonIcon_Magikarp,
    [SPECIES_GYARADOS] = gMonIcon_Gyarados,
    [SPECIES_LAPRAS] = gMonIcon_Lapras,
    [SPECIES_DITTO] = gMonIcon_Ditto,
    [SPECIES_EEVEE] = gMonIcon_Eevee,
    [SPECIES_VAPOREON] = gMonIcon_Vaporeon,
    [SPECIES_JOLTEON] = gMonIcon_Jolteon,
    [SPECIES_FLAREON] = gMonIcon_Flareon,
    [SPECIES_PORYGON] = gMonIcon_Porygon,
    [SPECIES_SKORUPI] = gMonIcon_Omanyte,
    [SPECIES_DRAPION] = gMonIcon_Omastar,
    [SPECIES_SKRELP] = gMonIcon_Kabuto,
    [SPECIES_DRAGALGE] = gMonIcon_Kabutops,
    [SPECIES_AERODACTYL] = gMonIcon_Aerodactyl,
    [SPECIES_SNORLAX] = gMonIcon_Snorlax,
    [SPECIES_ARTICUNO] = gMonIcon_Articuno,
    [SPECIES_ZAPDOS] = gMonIcon_Zapdos,
    [SPECIES_MOLTRES] = gMonIcon_Moltres,
    [SPECIES_GOOMY] = gMonIcon_Dratini,
    [SPECIES_SLIGGOO] = gMonIcon_Dragonair,
    [SPECIES_GOODRA] = gMonIcon_Dragonite,
    [SPECIES_MEWTWO] = gMonIcon_Mewtwo,
    [SPECIES_MEW] = gMonIcon_Mew,
    [SPECIES_SNOVER] = gMonIcon_Chikorita,
    [SPECIES_ABOMASNOW] = gMonIcon_Bayleef,
    [SPECIES_ABOMACIER] = gMonIcon_Meganium,
    [SPECIES_CYNDAQUIL] = gMonIcon_Cyndaquil,
    [SPECIES_QUILAVA] = gMonIcon_Quilava,
    [SPECIES_TYPHLOSION] = gMonIcon_Typhlosion,
    [SPECIES_WIMPOD] = gMonIcon_Totodile,
    [SPECIES_GOLISOPOD] = gMonIcon_Croconaw,
    [SPECIES_BASCULIN] = gMonIcon_Feraligatr,
    [SPECIES_SENTRET] = gMonIcon_Sentret,
    [SPECIES_FURRET] = gMonIcon_Furret,
    [SPECIES_FERROSEED] = gMonIcon_Hoothoot,
    [SPECIES_FERROTHORN] = gMonIcon_Noctowl,
    [SPECIES_CLAUNCHER] = gMonIcon_Ledyba,
    [SPECIES_CLAWITZER] = gMonIcon_Ledian,
    [SPECIES_SEWADDLE] = gMonIcon_Spinarak,
    [SPECIES_SWADLOON] = gMonIcon_Ariados,
    [SPECIES_LEAVANNY] = gMonIcon_Crobat,
    [SPECIES_CHINCHOU] = gMonIcon_Chinchou,
    [SPECIES_LANTURN] = gMonIcon_Lanturn,
    [SPECIES_FOONGUS] = gMonIcon_Pichu,
    [SPECIES_AMOONGUSS] = gMonIcon_Cleffa,
    [SPECIES_MIMIKYU] = gMonIcon_Igglybuff,
    [SPECIES_TOGEPI] = gMonIcon_Togepi,
    [SPECIES_TOGETIC] = gMonIcon_Togetic,
    [SPECIES_TOGEKISS] = gMonIcon_Natu,
    [SPECIES_PHANTUMP] = gMonIcon_Xatu,
    [SPECIES_MAREEP] = gMonIcon_Mareep,
    [SPECIES_FLAAFFY] = gMonIcon_Flaaffy,
    [SPECIES_AMPHAROS] = gMonIcon_Ampharos,
    [SPECIES_TREVENANT] = gMonIcon_Bellossom,
    [SPECIES_MARILL] = gMonIcon_Marill,
    [SPECIES_AZUMARILL] = gMonIcon_Azumarill,
    [SPECIES_GIBLE] = gMonIcon_Sudowoodo,
    [SPECIES_GABITE] = gMonIcon_Politoed,
    [SPECIES_GARCHOMP] = gMonIcon_Hoppip,
    [SPECIES_HONEDGE] = gMonIcon_Skiploom,
    [SPECIES_DOUBLADE] = gMonIcon_Jumpluff,
    [SPECIES_AEGISLASH] = gMonIcon_Aipom,
    [SPECIES_SCIMITEYE] = gMonIcon_Sunkern,
    [SPECIES_JAWGUILE] = gMonIcon_Sunflora,
    [SPECIES_YANMA] = gMonIcon_Yanma,
    [SPECIES_WOOPER] = gMonIcon_Wooper,
    [SPECIES_QUAGSIRE] = gMonIcon_Quagsire,
    [SPECIES_ESPEON] = gMonIcon_Espeon,
    [SPECIES_UMBREON] = gMonIcon_Umbreon,
    [SPECIES_LEAFEON] = gMonIcon_Murkrow,
    [SPECIES_GLACEON] = gMonIcon_Slowking,
    [SPECIES_SYLVEON] = gMonIcon_Misdreavus,
    [SPECIES_FLABEBE] = gMonIcon_UnownA,
    [SPECIES_FLOETTE] = gMonIcon_Wobbuffet,
    [SPECIES_FLORGES] = gMonIcon_Girafarig,
    [SPECIES_JOLTIK] = gMonIcon_Pineco,
    [SPECIES_GALVANTULA] = gMonIcon_Forretress,
    [SPECIES_AUDINO] = gMonIcon_Dunsparce,
    [SPECIES_GLIGAR] = gMonIcon_Gligar,
    [SPECIES_STEELIX] = gMonIcon_Steelix,
    [SPECIES_POPPLIO] = gMonIcon_Snubbull,
    [SPECIES_BRIONNE] = gMonIcon_Granbull,
    [SPECIES_PRIMARINA] = gMonIcon_Qwilfish,
    [SPECIES_SCIZOR] = gMonIcon_Scizor,
    [SPECIES_MEDIREIGN] = gMonIcon_Shuckle,
    [SPECIES_HERACROSS] = gMonIcon_Heracross,
    [SPECIES_SNEASEL] = gMonIcon_Sneasel,
    [SPECIES_TEDDIURSA] = gMonIcon_Teddiursa,
    [SPECIES_URSARING] = gMonIcon_Ursaring,
    [SPECIES_BRONZOR] = gMonIcon_Slugma,
    [SPECIES_BRONZONG] = gMonIcon_Magcargo,
    [SPECIES_SWINUB] = gMonIcon_Swinub,
    [SPECIES_PILOSWINE] = gMonIcon_Piloswine,
    [SPECIES_MAMOSWINE] = gMonIcon_Corsola,
    [SPECIES_ZEKROM] = gMonIcon_Remoraid,
    [SPECIES_SHINX] = gMonIcon_Octillery,
    [SPECIES_LUXIO] = gMonIcon_Delibird,
    [SPECIES_LUXRAY] = gMonIcon_Mantine,
    [SPECIES_SKARMORY] = gMonIcon_Skarmory,
    [SPECIES_HOUNDOUR] = gMonIcon_Houndour,
    [SPECIES_HOUNDOOM] = gMonIcon_Houndoom,
    [SPECIES_HOUNDREAD] = gMonIcon_Kingdra,
    [SPECIES_LITLEO] = gMonIcon_Phanpy,
    [SPECIES_PYROAR] = gMonIcon_Donphan,
    [SPECIES_PORYGON2] = gMonIcon_Porygon2,
    [SPECIES_RESHIRAM] = gMonIcon_Stantler,
    [SPECIES_SMEARGLE] = gMonIcon_Smeargle,
    [SPECIES_TYROGUE] = gMonIcon_Tyrogue,
    [SPECIES_HITMONTOP] = gMonIcon_Hitmontop,
    [SPECIES_GOTHITA] = gMonIcon_Smoochum,
    [SPECIES_GOTHORITA] = gMonIcon_Elekid,
    [SPECIES_GOTHITELLE] = gMonIcon_Magby,
    [SPECIES_MILTANK] = gMonIcon_Miltank,
    [SPECIES_BLISSEY] = gMonIcon_Blissey,
    [SPECIES_RAIKOU] = gMonIcon_Raikou,
    [SPECIES_ENTEI] = gMonIcon_Entei,
    [SPECIES_SUICUNE] = gMonIcon_Suicune,
    [SPECIES_LARVITAR] = gMonIcon_Larvitar,
    [SPECIES_PUPITAR] = gMonIcon_Pupitar,
    [SPECIES_TYRANITAR] = gMonIcon_Tyranitar,
    [SPECIES_LUGIA] = gMonIcon_Lugia,
    [SPECIES_HO_OH] = gMonIcon_HoOh,
    [SPECIES_CELEBI] = gMonIcon_Celebi,
    [SPECIES_OLD_UNOWN_B] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_C] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_D] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_E] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_F] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_G] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_H] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_I] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_J] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_K] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_L] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_M] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_N] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_O] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_P] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_Q] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_R] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_S] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_T] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_U] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_V] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_W] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_X] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_Y] = gMonIcon_QuestionMark,
    [SPECIES_OLD_UNOWN_Z] = gMonIcon_QuestionMark,
    [SPECIES_TREECKO] = gMonIcon_Treecko,
    [SPECIES_GROVYLE] = gMonIcon_Grovyle,
    [SPECIES_SCEPTILE] = gMonIcon_Sceptile,
    [SPECIES_TORCHIC] = gMonIcon_Torchic,
    [SPECIES_COMBUSKEN] = gMonIcon_Combusken,
    [SPECIES_BLAZIKEN] = gMonIcon_Blaziken,
    [SPECIES_MUDKIP] = gMonIcon_Mudkip,
    [SPECIES_MARSHTOMP] = gMonIcon_Marshtomp,
    [SPECIES_SWAMPERT] = gMonIcon_Swampert,
    [SPECIES_POOCHYENA] = gMonIcon_Poochyena,
    [SPECIES_MIGHTYENA] = gMonIcon_Mightyena,
    [SPECIES_ZIGZAGOON] = gMonIcon_Zigzagoon,
    [SPECIES_LINOONE] = gMonIcon_Linoone,
    [SPECIES_PETILIL] = gMonIcon_Wurmple,
    [SPECIES_LILLIGANT] = gMonIcon_Silcoon,
    [SPECIES_COTTONEE] = gMonIcon_Beautifly,
    [SPECIES_WHIMSICOTT] = gMonIcon_Cascoon,
    [SPECIES_SOLOSIS] = gMonIcon_Dustox,
    [SPECIES_DUOSIS] = gMonIcon_Lotad,
    [SPECIES_REUNICLUS] = gMonIcon_Lombre,
    [SPECIES_PANGORO] = gMonIcon_Ludicolo,
    [SPECIES_PANCHAM] = gMonIcon_Seedot,
    [SPECIES_MIENFOO] = gMonIcon_Nuzleaf,
    [SPECIES_MIENSHAO] = gMonIcon_Shiftry,
    [SPECIES_AMAURA] = gMonIcon_Nincada,
    [SPECIES_AURORUS] = gMonIcon_Ninjask,
    [SPECIES_DIALGA] = gMonIcon_Shedinja,
    [SPECIES_TAILLOW] = gMonIcon_Taillow,
    [SPECIES_SWELLOW] = gMonIcon_Swellow,
    [SPECIES_SHROOMISH] = gMonIcon_Shroomish,
    [SPECIES_BRELOOM] = gMonIcon_Breloom,
    [SPECIES_PALKIA] = gMonIcon_Spinda,
    [SPECIES_WINGULL] = gMonIcon_Wingull,
    [SPECIES_PELIPPER] = gMonIcon_Pelipper,
    [SPECIES_RIOLU] = gMonIcon_Surskit,
    [SPECIES_LUCARIO] = gMonIcon_Masquerain,
    [SPECIES_WAILMER] = gMonIcon_Wailmer,
    [SPECIES_WAILORD] = gMonIcon_Wailord,
    [SPECIES_SKITTY] = gMonIcon_Skitty,
    [SPECIES_DELCATTY] = gMonIcon_Delcatty,
    [SPECIES_ROGGENROLA] = gMonIcon_Kecleon,
    [SPECIES_BOLDORE] = gMonIcon_Baltoy,
    [SPECIES_GIGALITH] = gMonIcon_Claydol,
    [SPECIES_SANDSHREW_A] = gMonIcon_Nosepass,
    [SPECIES_SANDSLASH_A] = gMonIcon_Torkoal,
    [SPECIES_SABLEYE] = gMonIcon_Sableye,
    [SPECIES_LITWICK] = gMonIcon_Barboach,
    [SPECIES_LAMPENT] = gMonIcon_Whiscash,
    [SPECIES_CHANDELURE] = gMonIcon_Luvdisc,
    [SPECIES_CORPHISH] = gMonIcon_Corphish,
    [SPECIES_CRAWDAUNT] = gMonIcon_Crawdaunt,
    [SPECIES_FEEBAS] = gMonIcon_Feebas,
    [SPECIES_MILOTIC] = gMonIcon_Milotic,
    [SPECIES_CARVANHA] = gMonIcon_Carvanha,
    [SPECIES_SHARPEDO] = gMonIcon_Sharpedo,
    [SPECIES_TRAPINCH] = gMonIcon_Trapinch,
    [SPECIES_VIBRAVA] = gMonIcon_Vibrava,
    [SPECIES_FLYGON] = gMonIcon_Flygon,
    [SPECIES_DWEBBLE] = gMonIcon_Makuhita,
    [SPECIES_CRUSTLE] = gMonIcon_Hariyama,
    [SPECIES_ELECTRIKE] = gMonIcon_Electrike,
    [SPECIES_MANECTRIC] = gMonIcon_Manectric,
    [SPECIES_MANETHUNDR] = gMonIcon_Numel,
    [SPECIES_PORYGON_Z] = gMonIcon_Camerupt,
    [SPECIES_TYNAMO] = gMonIcon_Spheal,
    [SPECIES_EELEKTRIK] = gMonIcon_Sealeo,
    [SPECIES_EELEKTROSS] = gMonIcon_Walrein,
    [SPECIES_CACNEA] = gMonIcon_Cacnea,
    [SPECIES_CACTURNE] = gMonIcon_Cacturne,
    [SPECIES_SNORUNT] = gMonIcon_Snorunt,
    [SPECIES_GLALIE] = gMonIcon_Glalie,
    [SPECIES_FROSLASS] = gMonIcon_Lunatone,
    [SPECIES_TIRTOUGA] = gMonIcon_Solrock,
    [SPECIES_CARRACOSTA] = gMonIcon_Azurill,
    [SPECIES_SPOINK] = gMonIcon_Spoink,
    [SPECIES_GRUMPIG] = gMonIcon_Grumpig,
    [SPECIES_SALANDIT] = gMonIcon_Plusle,
    [SPECIES_SALAZZLE] = gMonIcon_Minun,
    [SPECIES_MAWILE] = gMonIcon_Mawile,
    [SPECIES_MEDITITE] = gMonIcon_Meditite,
    [SPECIES_MEDICHAM] = gMonIcon_Medicham,
    [SPECIES_SWABLU] = gMonIcon_Swablu,
    [SPECIES_ALTARIA] = gMonIcon_Altaria,
    [SPECIES_TIMBURR] = gMonIcon_Wynaut,
    [SPECIES_GURDURR] = gMonIcon_Duskull,
    [SPECIES_CONKELDURR] = gMonIcon_Dusclops,
    [SPECIES_GIRATINA] = gMonIcon_Roselia,
    [SPECIES_FLETCHLING] = gMonIcon_Slakoth,
    [SPECIES_FLETCHINDR] = gMonIcon_Vigoroth,
    [SPECIES_TALONFLAME] = gMonIcon_Slaking,
    [SPECIES_DARKRAI] = gMonIcon_Gulpin,
    [SPECIES_SWALOT] = gMonIcon_Swalot,
    [SPECIES_KYUREM] = gMonIcon_Tropius,
    [SPECIES_XERNEAS] = gMonIcon_Whismur,
    [SPECIES_YVELTAL] = gMonIcon_Loudred,
    [SPECIES_ZYGARDE] = gMonIcon_Exploud,
    [SPECIES_AZELF] = gMonIcon_Clamperl,
    [SPECIES_MESPRIT] = gMonIcon_Huntail,
    [SPECIES_UXIE] = gMonIcon_Gorebyss,
    [SPECIES_ABSOL] = gMonIcon_Absol,
    [SPECIES_SHUPPET] = gMonIcon_Shuppet,
    [SPECIES_BANETTE] = gMonIcon_Banette,
    [SPECIES_BANSHEETTE] = gMonIcon_Seviper,
    [SPECIES_ABSOLOM] = gMonIcon_Zangoose,
    [SPECIES_RELICANTH] = gMonIcon_Relicanth,
    [SPECIES_ARON] = gMonIcon_Aron,
    [SPECIES_LAIRON] = gMonIcon_Lairon,
    [SPECIES_AGGRON] = gMonIcon_Aggron,
    [SPECIES_CELEBI] = gMonIcon_Castform,
    [SPECIES_RHYPERIOR] = gMonIcon_Volbeat,
    [SPECIES_GALLADE] = gMonIcon_Illumise,
    [SPECIES_LILEEP] = gMonIcon_Lileep,
    [SPECIES_CRADILY] = gMonIcon_Cradily,
    [SPECIES_ANORITH] = gMonIcon_Anorith,
    [SPECIES_ARMALDO] = gMonIcon_Armaldo,
    [SPECIES_RALTS] = gMonIcon_Ralts,
    [SPECIES_KIRLIA] = gMonIcon_Kirlia,
    [SPECIES_GARDEVOIR] = gMonIcon_Gardevoir,
    [SPECIES_BAGON] = gMonIcon_Bagon,
    [SPECIES_SHELGON] = gMonIcon_Shelgon,
    [SPECIES_SALAMENCE] = gMonIcon_Salamence,
    [SPECIES_BELDUM] = gMonIcon_Beldum,
    [SPECIES_METANG] = gMonIcon_Metang,
    [SPECIES_METAGROSS] = gMonIcon_Metagross,
    [SPECIES_REGIROCK] = gMonIcon_Regirock,
    [SPECIES_REGICE] = gMonIcon_Regice,
    [SPECIES_REGISTEEL] = gMonIcon_Registeel,
    [SPECIES_KYOGRE] = gMonIcon_Kyogre,
    [SPECIES_GROUDON] = gMonIcon_Groudon,
    [SPECIES_RAYQUAZA] = gMonIcon_Rayquaza,
    [SPECIES_LATIAS] = gMonIcon_Latias,
    [SPECIES_LATIOS] = gMonIcon_Latios,
    [SPECIES_JIRACHI] = gMonIcon_Jirachi,
    [SPECIES_DEOXYS] = gMonIcon_Deoxys,
    [SPECIES_ARCEUS] = gMonIcon_Chimecho,
    [SPECIES_EGG] = gMonIcon_Egg,
    [SPECIES_FLABEBE_B] = gMonIcon_UnownB,
    [SPECIES_FLABEBE_C] = gMonIcon_UnownC,
    [SPECIES_FLABEBE_D] = gMonIcon_UnownD,
    [SPECIES_FLABEBE_E] = gMonIcon_UnownE,
    [SPECIES_FLABEBE_F] = gMonIcon_UnownF,
    [SPECIES_FLABEBE_G] = gMonIcon_UnownG,
    [SPECIES_FLABEBE_H] = gMonIcon_UnownH,
    [SPECIES_FLABEBE_I] = gMonIcon_UnownI,
    [SPECIES_FLABEBE_J] = gMonIcon_UnownJ,
    [SPECIES_FLABEBE_K] = gMonIcon_UnownK,
    [SPECIES_FLABEBE_L] = gMonIcon_UnownL,
    [SPECIES_FLABEBE_M] = gMonIcon_UnownM,
    [SPECIES_FLABEBE_N] = gMonIcon_UnownN,
    [SPECIES_FLABEBE_O] = gMonIcon_UnownO,
    [SPECIES_FLABEBE_P] = gMonIcon_UnownP,
    [SPECIES_FLABEBE_Q] = gMonIcon_UnownQ,
    [SPECIES_FLABEBE_R] = gMonIcon_UnownR,
    [SPECIES_FLABEBE_S] = gMonIcon_UnownS,
    [SPECIES_FLABEBE_T] = gMonIcon_UnownT,
    [SPECIES_FLABEBE_U] = gMonIcon_UnownU,
    [SPECIES_FLABEBE_V] = gMonIcon_UnownV,
    [SPECIES_FLABEBE_W] = gMonIcon_UnownW,
    [SPECIES_FLABEBE_X] = gMonIcon_UnownX,
    [SPECIES_FLABEBE_Y] = gMonIcon_UnownY,
    [SPECIES_FLABEBE_Z] = gMonIcon_UnownZ,
    [SPECIES_FLABEBE_EMARK] = gMonIcon_UnownExclamationMark,
    [SPECIES_FLABEBE_QMARK] = gMonIcon_UnownQuestionMark,
};

const u8 gMonIconPaletteIndices[] =
{
    [SPECIES_NONE] = 0,
    [SPECIES_BULBASAUR] = 1,
    [SPECIES_IVYSAUR] = 1,
    [SPECIES_VENUSAUR] = 1,
    [SPECIES_CHARMANDER] = 0,
    [SPECIES_CHARMELEON] = 0,
    [SPECIES_CHARIZARD] = 0,
    [SPECIES_SQUIRTLE] = 0,
    [SPECIES_WARTORTLE] = 2,
    [SPECIES_BLASTOISE] = 2,
    [SPECIES_SNIVY] = 1,
    [SPECIES_SERVINE] = 1,
    [SPECIES_SERPERIOR] = 0,
    [SPECIES_WEEDLE] = 1,
    [SPECIES_KAKUNA] = 2,
    [SPECIES_BEEDRILL] = 2,
    [SPECIES_PIDGEY] = 0,
    [SPECIES_PIDGEOTTO] = 0,
    [SPECIES_PIDGEOT] = 0,
    [SPECIES_RATTATA] = 2,
    [SPECIES_RATICATE] = 1,
    [SPECIES_NOIBAT] = 0,
    [SPECIES_NOIVERN] = 0,
    [SPECIES_EKANS] = 2,
    [SPECIES_ARBOK] = 2,
    [SPECIES_PIKACHU] = 2,
    [SPECIES_RAICHU] = 0,
    [SPECIES_SANDSHREW] = 2,
    [SPECIES_SANDSLASH] = 2,
    [SPECIES_NIDORAN_F] = 2,
    [SPECIES_NIDORINA] = 2,
    [SPECIES_NIDOQUEEN] = 2,
    [SPECIES_NIDORAN_M] = 2,
    [SPECIES_NIDORINO] = 2,
    [SPECIES_NIDOKING] = 2,
    [SPECIES_CLEFAIRY] = 0,
    [SPECIES_CLEFABLE] = 0,
    [SPECIES_VULPIX] = 2,
    [SPECIES_NINETALES] = 1,
    [SPECIES_FROAKIE] = 0,
    [SPECIES_FROGADIER] = 0,
    [SPECIES_GRENINJA] = 2,
    [SPECIES_DURANT] = 2,
    [SPECIES_ROWLET] = 1,
    [SPECIES_DARTRIX] = 0,
    [SPECIES_DECIDUEYE] = 0,
    [SPECIES_BIDOOF] = 0,
    [SPECIES_BIBAREL] = 0,
    [SPECIES_VENONAT] = 0,
    [SPECIES_VENOMOTH] = 2,
    [SPECIES_KARRABLAST] = 2,
    [SPECIES_ESCAVALIER] = 2,
    [SPECIES_TYRUNT] = 1,
    [SPECIES_TYRANTRUM] = 1,
    [SPECIES_PSYDUCK] = 1,
    [SPECIES_VESPIQUEEN] = 2,
    [SPECIES_PURRLOIN] = 1,
    [SPECIES_LIEPARD] = 2,
    [SPECIES_GROWLITHE] = 0,
    [SPECIES_ARCANINE] = 0,
    [SPECIES_PIDOVE] = 0,
    [SPECIES_TRANQUILL] = 0,
    [SPECIES_UNFEZANT] = 0,
    [SPECIES_ABRA] = 2,
    [SPECIES_KADABRA] = 2,
    [SPECIES_ALAKAZAM] = 2,
    [SPECIES_SCATTERBUG] = 0,
    [SPECIES_SPEWPA] = 2,
    [SPECIES_VIVILLON] = 0,
    [SPECIES_VENIPEDE] = 1,
    [SPECIES_WHIRLIPEDE] = 1,
    [SPECIES_SCOLIPEDE] = 1,
    [SPECIES_TENTACOOL] = 2,
    [SPECIES_TENTACRUEL] = 2,
    [SPECIES_ESPURR] = 1,
    [SPECIES_MEOWSTIC_M] = 1,
    [SPECIES_MEOWSTIC_F] = 1,
    [SPECIES_PONYTA] = 0,
    [SPECIES_RAPIDASH] = 0,
    [SPECIES_VULLABY] = 0,
    [SPECIES_MANDIBUZZ] = 0,
    [SPECIES_MAGNEMITE] = 0,
    [SPECIES_MAGNETON] = 0,
    [SPECIES_MAGNEZONE = 1,
    [SPECIES_ROTOM] = 2,
    [SPECIES_LILLIPUP] = 2,
    [SPECIES_HERDIER] = 2,
    [SPECIES_STOUTLAND] = 2,
    [SPECIES_MUDBRAY] = 2,
    [SPECIES_MUDSDALE] = 2,
    [SPECIES_DUCKLETT] = 2,
    [SPECIES_SWANNA] = 2,
    [SPECIES_GASTLY] = 2,
    [SPECIES_HAUNTER] = 2,
    [SPECIES_GENGAR] = 2,
    [SPECIES_ONIX] = 2,
    [SPECIES_RUFFLET] = 2,
    [SPECIES_BRAVIARY] = 1,
    [SPECIES_KRABBY] = 2,
    [SPECIES_KINGLER] = 2,
    [SPECIES_SCRAGGY] = 0,
    [SPECIES_SCRAFTY] = 0,
    [SPECIES_CUBCHOO] = 0,
    [SPECIES_BEARTIC] = 1,
    [SPECIES_CUBONE] = 1,
    [SPECIES_MAROWAK] = 1,
    [SPECIES_HITMONLEE] = 2,
    [SPECIES_HITMONCHAN] = 2,
    [SPECIES_BUNNELBY] = 1,
    [SPECIES_DIGGERSBY] = 2,
    [SPECIES_EMOLGA] = 2,
    [SPECIES_RHYHORN] = 1,
    [SPECIES_RHYDON] = 1,
    [SPECIES_CHANSEY] = 0,
    [SPECIES_TANGELA] = 0,
    [SPECIES_TANGROWTH] = 1,
    [SPECIES_SCRAGGY] = 0,
    [SPECIES_SCRAFTY] = 0,
    [SPECIES_DRILBUR] = 0,
    [SPECIES_EXCADRILL] = 0,
    [SPECIES_STARYU] = 2,
    [SPECIES_STARMIE] = 2,
    [SPECIES_PACHIRISU] = 0,
    [SPECIES_SCYTHER] = 1,
    [SPECIES_LARVESTA] = 2,
    [SPECIES_VOLCARONA] = 1,
    [SPECIES_BUIZEL] = 0,
    [SPECIES_PINSIR] = 2,
    [SPECIES_FLOATZEL] = 2,
    [SPECIES_MAGIKARP] = 0,
    [SPECIES_GYARADOS] = 0,
    [SPECIES_LAPRAS] = 2,
    [SPECIES_DITTO] = 2,
    [SPECIES_EEVEE] = 2,
    [SPECIES_VAPOREON] = 0,
    [SPECIES_JOLTEON] = 0,
    [SPECIES_FLAREON] = 0,
    [SPECIES_PORYGON] = 0,
    [SPECIES_SKORUPI] = 0,
    [SPECIES_DRAPION] = 0,
    [SPECIES_SKRELP] = 2,
    [SPECIES_DRAGALGE] = 2,
    [SPECIES_AERODACTYL] = 0,
    [SPECIES_SNORLAX] = 1,
    [SPECIES_ARTICUNO] = 0,
    [SPECIES_ZAPDOS] = 0,
    [SPECIES_MOLTRES] = 0,
    [SPECIES_GOOMY] = 0,
    [SPECIES_SLIGGOO] = 0,
    [SPECIES_GOODRA] = 2,
    [SPECIES_MEWTWO] = 2,
    [SPECIES_MEW] = 0,
    [SPECIES_SNOVER] = 1,
    [SPECIES_ABOMASNOW] = 1,
    [SPECIES_ABOMACIER] = 1,
    [SPECIES_CYNDAQUIL] = 1,
    [SPECIES_QUILAVA] = 1,
    [SPECIES_TYPHLOSION] = 1,
    [SPECIES_WIMPOD] = 2,
    [SPECIES_GOLISOPOD] = 2,
    [SPECIES_BASCULIN] = 2,
    [SPECIES_SENTRET] = 2,
    [SPECIES_FURRET] = 2,
    [SPECIES_FERROSEED] = 2,
    [SPECIES_FERROTHORN] = 2,
    [SPECIES_CLAUNCHER] = 0,
    [SPECIES_CLAWITZER] = 0,
    [SPECIES_SEWADDLE] = 1,
    [SPECIES_SWADLOON] = 0,
    [SPECIES_LEAVANNY] = 2,
    [SPECIES_CHINCHOU] = 2,
    [SPECIES_LANTURN] = 0,
    [SPECIES_FOONGUS] = 0,
    [SPECIES_AMOONGUSS] = 0,
    [SPECIES_MIMIKYU] = 1,
    [SPECIES_TOGEPI] = 2,
    [SPECIES_TOGETIC] = 2,
    [SPECIES_TOGEKISS] = 0,
    [SPECIES_PHANTUMP] = 0,
    [SPECIES_MAREEP] = 2,
    [SPECIES_FLAAFFY] = 0,
    [SPECIES_AMPHAROS] = 0,
    [SPECIES_TREVENANT] = 1,
    [SPECIES_MARILL] = 2,
    [SPECIES_AZUMARILL] = 2,
    [SPECIES_GIBLE] = 1,
    [SPECIES_GABITE] = 1,
    [SPECIES_GARCHOMP] = 1,
    [SPECIES_HONEDGE] = 1,
    [SPECIES_DOUBLADE] = 2,
    [SPECIES_AEGISLASH] = 2,
    [SPECIES_SCIMITEYE] = 1,
    [SPECIES_JAWGUILE] = 1,
    [SPECIES_YANMA] = 1,
    [SPECIES_WOOPER] = 0,
    [SPECIES_QUAGSIRE] = 0,
    [SPECIES_ESPEON] = 2,
    [SPECIES_UMBREON] = 2,
    [SPECIES_LEAFEON] = 2,
    [SPECIES_GLACEON] = 0,
    [SPECIES_SYLVEON] = 0,
    [SPECIES_FLABEBE] = 0,
    [SPECIES_FLOETTE] = 0,
    [SPECIES_FLORGES] = 1,
    [SPECIES_JOLTIK] = 0,
    [SPECIES_GALVANTULA] = 2,
    [SPECIES_AUDINO] = 2,
    [SPECIES_GLIGAR] = 2,
    [SPECIES_STEELIX] = 0,
    [SPECIES_POPPLIO] = 0,
    [SPECIES_BRIONNE] = 2,
    [SPECIES_PRIMARINA] = 0,
    [SPECIES_SCIZOR] = 0,
    [SPECIES_MEDIREIGN] = 1,
    [SPECIES_HERACROSS] = 2,
    [SPECIES_SNEASEL] = 0,
    [SPECIES_TEDDIURSA] = 0,
    [SPECIES_URSARING] = 2,
    [SPECIES_BRONZOR] = 0,
    [SPECIES_BRONZONG] = 0,
    [SPECIES_SWINUB] = 2,
    [SPECIES_PILOSWINE] = 2,
    [SPECIES_MAMOSWINE] = 0,
    [SPECIES_ZEKROM] = 0,
    [SPECIES_SHINX] = 0,
    [SPECIES_LUXIO] = 0,
    [SPECIES_LUXRAY] = 2,
    [SPECIES_SKARMORY] = 0,
    [SPECIES_HOUNDOUR] = 0,
    [SPECIES_HOUNDOOM] = 0,
    [SPECIES_HOUNDREAD] = 0,
    [SPECIES_LITLEO] = 0,
    [SPECIES_PYROAR] = 0,
    [SPECIES_PORYGON2] = 0,
    [SPECIES_RESHIRAM] = 2,
    [SPECIES_SMEARGLE] = 1,
    [SPECIES_TYROGUE] = 2,
    [SPECIES_HITMONTOP] = 2,
    [SPECIES_GOTHITA] = 1,
    [SPECIES_GOTHORITA] = 1,
    [SPECIES_GOTHITELLE] = 1,
    [SPECIES_MILTANK] = 1,
    [SPECIES_BLISSEY] = 1,
    [SPECIES_RAIKOU] = 0,
    [SPECIES_ENTEI] = 2,
    [SPECIES_SUICUNE] = 0,
    [SPECIES_LARVITAR] = 1,
    [SPECIES_PUPITAR] = 0,
    [SPECIES_TYRANITAR] = 1,
    [SPECIES_LUGIA] = 0,
    [SPECIES_HO_OH] = 1,
    [SPECIES_CELEBI] = 1,
    [SPECIES_OLD_UNOWN_B] = 0,
    [SPECIES_OLD_UNOWN_C] = 0,
    [SPECIES_OLD_UNOWN_D] = 0,
    [SPECIES_OLD_UNOWN_E] = 0,
    [SPECIES_OLD_UNOWN_F] = 0,
    [SPECIES_OLD_UNOWN_G] = 0,
    [SPECIES_OLD_UNOWN_H] = 0,
    [SPECIES_OLD_UNOWN_I] = 0,
    [SPECIES_OLD_UNOWN_J] = 0,
    [SPECIES_OLD_UNOWN_K] = 0,
    [SPECIES_OLD_UNOWN_L] = 0,
    [SPECIES_OLD_UNOWN_M] = 0,
    [SPECIES_OLD_UNOWN_N] = 0,
    [SPECIES_OLD_UNOWN_O] = 0,
    [SPECIES_OLD_UNOWN_P] = 0,
    [SPECIES_OLD_UNOWN_Q] = 0,
    [SPECIES_OLD_UNOWN_R] = 0,
    [SPECIES_OLD_UNOWN_S] = 0,
    [SPECIES_OLD_UNOWN_T] = 0,
    [SPECIES_OLD_UNOWN_U] = 0,
    [SPECIES_OLD_UNOWN_V] = 0,
    [SPECIES_OLD_UNOWN_W] = 0,
    [SPECIES_OLD_UNOWN_X] = 0,
    [SPECIES_OLD_UNOWN_Y] = 0,
    [SPECIES_OLD_UNOWN_Z] = 0,
    [SPECIES_TREECKO] = 1,
    [SPECIES_GROVYLE] = 0,
    [SPECIES_SCEPTILE] = 1,
    [SPECIES_TORCHIC] = 0,
    [SPECIES_COMBUSKEN] = 0,
    [SPECIES_BLAZIKEN] = 0,
    [SPECIES_MUDKIP] = 0,
    [SPECIES_MARSHTOMP] = 0,
    [SPECIES_SWAMPERT] = 0,
    [SPECIES_POOCHYENA] = 2,
    [SPECIES_MIGHTYENA] = 2,
    [SPECIES_ZIGZAGOON] = 2,
    [SPECIES_LINOONE] = 2,
    [SPECIES_PETILIL] = 0,
    [SPECIES_LILLIGANT] = 2,
    [SPECIES_COTTONEE] = 0,
    [SPECIES_WHIMSICOTT] = 2,
    [SPECIES_SOLOSIS] = 1,
    [SPECIES_DUOSIS] = 1,
    [SPECIES_REUNICLUS] = 1,
    [SPECIES_PANGORO] = 1,
    [SPECIES_PANCHAM] = 1,
    [SPECIES_MIENFOO] = 1,
    [SPECIES_MIENSHAO] = 0,
    [SPECIES_AMAURA] = 1,
    [SPECIES_AURORUS] = 1,
    [SPECIES_DIALGA] = 1,
    [SPECIES_TAILLOW] = 2,
    [SPECIES_SWELLOW] = 2,
    [SPECIES_SHROOMISH] = 1,
    [SPECIES_BRELOOM] = 1,
    [SPECIES_PALKIA] = 1,
    [SPECIES_WINGULL] = 0,
    [SPECIES_PELIPPER] = 0,
    [SPECIES_RIOLU] = 2,
    [SPECIES_LUCARIO] = 0,
    [SPECIES_WAILMER] = 2,
    [SPECIES_WAILORD] = 0,
    [SPECIES_SKITTY] = 0,
    [SPECIES_DELCATTY] = 2,
    [SPECIES_ROGGENROLA] = 1,
    [SPECIES_BOLDORE] = 1,
    [SPECIES_GIGALITH] = 0,
    [SPECIES_SANDSHREW_A] = 0,
    [SPECIES_SANDSLASH_A] = 1,
    [SPECIES_SABLEYE] = 2,
    [SPECIES_LITWICK] = 0,
    [SPECIES_LAMPENT] = 0,
    [SPECIES_CHANDELURE] = 0,
    [SPECIES_CORPHISH] = 0,
    [SPECIES_CRAWDAUNT] = 0,
    [SPECIES_FEEBAS] = 2,
    [SPECIES_MILOTIC] = 0,
    [SPECIES_CARVANHA] = 0,
    [SPECIES_SHARPEDO] = 0,
    [SPECIES_TRAPINCH] = 1,
    [SPECIES_VIBRAVA] = 1,
    [SPECIES_FLYGON] = 1,
    [SPECIES_DWEBBLE] = 2,
    [SPECIES_CRUSTLE] = 1,
    [SPECIES_ELECTRIKE] = 1,
    [SPECIES_MANECTRIC] = 0,
    [SPECIES_MANETHUNDR] = 1,
    [SPECIES_PORYGON_Z] = 0,
    [SPECIES_TYNAMO] = 2,
    [SPECIES_EELEKTRIK] = 2,
    [SPECIES_EELEKTROSS] = 0,
    [SPECIES_CACNEA] = 1,
    [SPECIES_CACTURNE] = 1,
    [SPECIES_SNORUNT] = 2,
    [SPECIES_GLALIE] = 0,
    [SPECIES_FROSLASS] = 1,
    [SPECIES_TIRTOUGA] = 0,
    [SPECIES_CARRACOSTA] = 2,
    [SPECIES_SPOINK] = 0,
    [SPECIES_GRUMPIG] = 2,
    [SPECIES_SALANDIT] = 0,
    [SPECIES_SALAZZLE] = 0,
    [SPECIES_MAWILE] = 2,
    [SPECIES_MEDITITE] = 0,
    [SPECIES_MEDICHAM] = 0,
    [SPECIES_SWABLU] = 0,
    [SPECIES_ALTARIA] = 0,
    [SPECIES_TIMBURR] = 0,
    [SPECIES_GURDURR] = 0,
    [SPECIES_CONKELDURR] = 0,
    [SPECIES_GIRATINA] = 0,
    [SPECIES_FLETCHLING] = 2,
    [SPECIES_FLETCHINDR] = 2,
    [SPECIES_TALONFLAME] = 1,
    [SPECIES_DARKRAI] = 1,
    [SPECIES_SWALOT] = 2,
    [SPECIES_KYUREM] = 1,
    [SPECIES_XERNEAS] = 0,
    [SPECIES_YVELTAL] = 2,
    [SPECIES_ZYGARDE] = 2,
    [SPECIES_AZELF] = 0,
    [SPECIES_MESPRIT] = 0,
    [SPECIES_UXIE] = 0,
    [SPECIES_ABSOL] = 0,
    [SPECIES_SHUPPET] = 0,
    [SPECIES_BANETTE] = 0,
    [SPECIES_BANSHEETTE] = 2,
    [SPECIES_ABSOLOM] = 0,
    [SPECIES_RELICANTH] = 1,
    [SPECIES_ARON] = 2,
    [SPECIES_LAIRON] = 2,
    [SPECIES_AGGRON] = 2,
    [SPECIES_CELEBI] = 0,
    [SPECIES_RHYPERIOR] = 0,
    [SPECIES_GALLADE] = 2,
    [SPECIES_LILEEP] = 2,
    [SPECIES_CRADILY] = 0,
    [SPECIES_ANORITH] = 0,
    [SPECIES_ARMALDO] = 0,
    [SPECIES_RALTS] = 1,
    [SPECIES_KIRLIA] = 1,
    [SPECIES_GARDEVOIR] = 1,
    [SPECIES_BAGON] = 2,
    [SPECIES_SHELGON] = 2,
    [SPECIES_SALAMENCE] = 0,
    [SPECIES_BELDUM] = 0,
    [SPECIES_METANG] = 0,
    [SPECIES_METAGROSS] = 0,
    [SPECIES_REGIROCK] = 2,
    [SPECIES_REGICE] = 2,
    [SPECIES_REGISTEEL] = 2,
    [SPECIES_KYOGRE] = 2,
    [SPECIES_GROUDON] = 0,
    [SPECIES_RAYQUAZA] = 1,
    [SPECIES_LATIAS] = 0,
    [SPECIES_LATIOS] = 2,
    [SPECIES_JIRACHI] = 0,
    [SPECIES_DEOXYS] = 0,
    [SPECIES_ARCEUS] = 0,
    [SPECIES_EGG] = 1,
    [SPECIES_FLABEBE_B] = 0,
    [SPECIES_FLABEBE_C] = 0,
    [SPECIES_FLABEBE_D] = 0,
    [SPECIES_FLABEBE_E] = 0,
    [SPECIES_FLABEBE_F] = 0,
    [SPECIES_FLABEBE_G] = 0,
    [SPECIES_FLABEBE_H] = 0,
    [SPECIES_FLABEBE_I] = 0,
    [SPECIES_FLABEBE_J] = 0,
    [SPECIES_FLABEBE_K] = 0,
    [SPECIES_FLABEBE_L] = 0,
    [SPECIES_FLABEBE_M] = 0,
    [SPECIES_FLABEBE_N] = 0,
    [SPECIES_FLABEBE_O] = 0,
    [SPECIES_FLABEBE_P] = 0,
    [SPECIES_FLABEBE_Q] = 0,
    [SPECIES_FLABEBE_R] = 0,
    [SPECIES_FLABEBE_S] = 0,
    [SPECIES_FLABEBE_T] = 0,
    [SPECIES_FLABEBE_U] = 0,
    [SPECIES_FLABEBE_V] = 0,
    [SPECIES_FLABEBE_W] = 0,
    [SPECIES_FLABEBE_X] = 0,
    [SPECIES_FLABEBE_Y] = 0,
    [SPECIES_FLABEBE_Z] = 0,
    [SPECIES_FLABEBE_EMARK] = 0,
    [SPECIES_FLABEBE_QMARK] = 0,
};

const struct SpritePalette gMonIconPaletteTable[] =
{
    { gMonIconPalettes[0], POKE_ICON_BASE_PAL_TAG + 0 },
    { gMonIconPalettes[1], POKE_ICON_BASE_PAL_TAG + 1 },
    { gMonIconPalettes[2], POKE_ICON_BASE_PAL_TAG + 2 },

// There are only 3 actual palettes. The following are unused
// and don't point to valid data.
    { gMonIconPalettes[3], POKE_ICON_BASE_PAL_TAG + 3 },
    { gMonIconPalettes[4], POKE_ICON_BASE_PAL_TAG + 4 },
    { gMonIconPalettes[5], POKE_ICON_BASE_PAL_TAG + 5 },
};

const struct OamData sMonIconOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
};

// fastest to slowest

static const union AnimCmd sAnim_0[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_1[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_2[] =
{
    ANIMCMD_FRAME(0, 14),
    ANIMCMD_FRAME(1, 14),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_3[] =
{
    ANIMCMD_FRAME(0, 22),
    ANIMCMD_FRAME(1, 22),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_4[] =
{
    ANIMCMD_FRAME(0, 29),
    ANIMCMD_FRAME(0, 29), // frame 0 is repeated
    ANIMCMD_JUMP(0),
};

const union AnimCmd *const sMonIconAnims[] =
{
    sAnim_0,
    sAnim_1,
    sAnim_2,
    sAnim_3,
    sAnim_4,
};

static const union AffineAnimCmd sAffineAnim_0[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 0, 10),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_1[] =
{
    AFFINEANIMCMD_FRAME(-2, -2, 0, 122),
    AFFINEANIMCMD_END,
};

const union AffineAnimCmd *const sMonIconAffineAnims[] =
{
    sAffineAnim_0,
    sAffineAnim_1,
};

const u16 sSpriteImageSizes[3][4] =
{
    // square
    {
         0x20, // 1×1
         0x80, // 2×2
        0x200, // 4×4
        0x800, // 8×8
    },

    // horizontal rectangle
    {
         0x40, // 2×1
         0x80, // 4×1
        0x100, // 4×2
        0x400, // 8×4
    },

    // vertical rectangle
    {
         0x40, // 1×2
         0x80, // 1×4
        0x100, // 2×4
        0x400, // 4×8
    },
};

u8 CreateMonIcon(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u32 personality, bool32 extra)
{
    u8 spriteId;
    struct MonIconSpriteTemplate iconTemplate =
    {
        .oam = &sMonIconOamData,
        .image = GetMonIconPtr(species, personality, extra),
        .anims = sMonIconAnims,
        .affineAnims = sMonIconAffineAnims,
        .callback = callback,
        .paletteTag = POKE_ICON_BASE_PAL_TAG + gMonIconPaletteIndices[species],
    };

    if (species > NUM_SPECIES)
        iconTemplate.paletteTag = POKE_ICON_BASE_PAL_TAG;

    spriteId = CreateMonIconSprite(&iconTemplate, x, y, subpriority);

    UpdateMonIconFrame(&gSprites[spriteId]);

    return spriteId;
}

u8 sub_80D2D78(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, bool32 extra)
{
    u8 spriteId;
    struct MonIconSpriteTemplate iconTemplate =
    {
        .oam = &sMonIconOamData,
        .image = NULL,
        .anims = sMonIconAnims,
        .affineAnims = sMonIconAffineAnims,
        .callback = callback,
        .paletteTag = POKE_ICON_BASE_PAL_TAG + gMonIconPaletteIndices[species],
    };

    iconTemplate.image = GetMonIconTiles(species, extra);
    spriteId = CreateMonIconSprite(&iconTemplate, x, y, subpriority);

    UpdateMonIconFrame(&gSprites[spriteId]);

    return spriteId;
}

u16 GetIconSpecies(u16 species, u32 personality)
{
    u16 result;

    if (species == SPECIES_FLABEBE)
    {
        u16 letter = GetUnownLetterByPersonality(personality);
        if (letter == 0)
            letter = SPECIES_FLABEBE;
        else
            letter += (SPECIES_FLABEBE_B - 1);
        result = letter;
    }
    else
    {
        if (species > NUM_SPECIES)
            result = 260;
        else
            result = species;
    }

    return result;
}

u16 GetUnownLetterByPersonality(u32 personality)
{
    if (!personality)
        return 0;
    else
        return (((personality & 0x3000000) >> 18) | ((personality & 0x30000) >> 12) | ((personality & 0x300) >> 6) | (personality & 0x3)) % 0x1C;
}

u16 sub_80D2E84(u16 species)
{
    u16 value;

    if (MailSpeciesToSpecies(species, &value) == SPECIES_FLABEBE)
    {
        if (value == 0)
            value += SPECIES_FLABEBE;
        else
            value += (SPECIES_FLABEBE_B - 1);
        return value;
    }
    else
    {
        if (species > (SPECIES_FLABEBE_B - 1))
            species = SPECIES_OLD_UNOWN_J; // That's an oddly specific species.
        return GetIconSpecies(species, 0);
    }
}

const u8 *GetMonIconPtr(u16 species, u32 personality, bool32 extra)
{
    return GetMonIconTiles(GetIconSpecies(species, personality), extra);
}

void sub_80D2EF8(struct Sprite *sprite)
{
    sub_80D328C(sprite);
}

void LoadMonIconPalettes(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(gMonIconPaletteTable); i++)
        LoadSpritePalette(&gMonIconPaletteTable[i]);
}

// unused
void SafeLoadMonIconPalette(u16 species)
{
    u8 palIndex;
    if (species > NUM_SPECIES)
        species = 260;
    palIndex = gMonIconPaletteIndices[species];
    if (IndexOfSpritePaletteTag(gMonIconPaletteTable[palIndex].tag) == 0xFF)
        LoadSpritePalette(&gMonIconPaletteTable[palIndex]);
}

void LoadMonIconPalette(u16 species)
{
    u8 palIndex = gMonIconPaletteIndices[species];
    if (IndexOfSpritePaletteTag(gMonIconPaletteTable[palIndex].tag) == 0xFF)
        LoadSpritePalette(&gMonIconPaletteTable[palIndex]);
}

void FreeMonIconPalettes(void)
{
    u8 i;
    for (i = 0; i < 6; i++)
        FreeSpritePaletteByTag(gMonIconPaletteTable[i].tag);
}

// unused
void SafeFreeMonIconPalette(u16 species)
{
    u8 palIndex;
    if (species > NUM_SPECIES)
        species = 260;
    palIndex = gMonIconPaletteIndices[species];
    FreeSpritePaletteByTag(gMonIconPaletteTable[palIndex].tag);
}

void FreeMonIconPalette(u16 species)
{
    u8 palIndex;
    palIndex = gMonIconPaletteIndices[species];
    FreeSpritePaletteByTag(gMonIconPaletteTable[palIndex].tag);
}

void UpdateTradeMonIconFrame(struct Sprite *sprite)
{
    UpdateMonIconFrame(sprite);
}

const u8* GetMonIconTiles(u16 species, bool32 extra)
{
    const u8* iconSprite = gMonIconTable[species];
    if (species == SPECIES_DEOXYS && extra == TRUE)
    {
        iconSprite = (const u8*)(0x400 + (u32)iconSprite); //WTF?
    }
    return iconSprite;
}

void sub_80D304C(u16 offset)
{
    s32 i;
    const struct SpritePalette* monIconPalettePtr;

    if (offset <= 0xA0)
    {
        monIconPalettePtr = gMonIconPaletteTable;
        for(i = 5; i >= 0; i--)
        {
            LoadPalette(monIconPalettePtr->data, offset, 0x20);
            offset += 0x10;
            monIconPalettePtr++;
        }
    }
}

u8 GetValidMonIconPalIndex(u16 species)
{
    if (species > NUM_SPECIES)
        species = 260;
    return gMonIconPaletteIndices[species];
}

u8 GetMonIconPaletteIndexFromSpecies(u16 species)
{
    return gMonIconPaletteIndices[species];
}

const u16* GetValidMonIconPalettePtr(u16 species)
{
    if (species > NUM_SPECIES)
        species = 260;
    return gMonIconPaletteTable[gMonIconPaletteIndices[species]].data;
}

u8 UpdateMonIconFrame(struct Sprite *sprite)
{
    u8 result = 0;

    if (sprite->animDelayCounter == 0)
    {
        s16 frame = sprite->anims[sprite->animNum][sprite->animCmdIndex].frame.imageValue;

        switch (frame)
        {
        case -1:
            break;
        case -2:
            sprite->animCmdIndex = 0;
            break;
        default:
            RequestSpriteCopy(
                // pointer arithmetic is needed to get the correct pointer to perform the sprite copy on.
                // because sprite->images is a struct def, it has to be casted to (u8 *) before any
                // arithmetic can be performed.
                (u8 *)sprite->images + (sSpriteImageSizes[sprite->oam.shape][sprite->oam.size] * frame),
                (u8 *)(OBJ_VRAM0 + sprite->oam.tileNum * TILE_SIZE_4BPP),
                sSpriteImageSizes[sprite->oam.shape][sprite->oam.size]);
            sprite->animDelayCounter = sprite->anims[sprite->animNum][sprite->animCmdIndex].frame.duration & 0xFF;
            sprite->animCmdIndex++;
            result = sprite->animCmdIndex;
            break;
        }
    }
    else
    {
        sprite->animDelayCounter--;
    }
    return result;
}

static u8 CreateMonIconSprite(struct MonIconSpriteTemplate *iconTemplate, s16 x, s16 y, u8 subpriority)
{
    u8 spriteId;

    struct SpriteFrameImage image = { NULL, sSpriteImageSizes[iconTemplate->oam->shape][iconTemplate->oam->size] };

    struct SpriteTemplate spriteTemplate =
    {
        .tileTag = 0xFFFF,
        .paletteTag = iconTemplate->paletteTag,
        .oam = iconTemplate->oam,
        .anims = iconTemplate->anims,
        .images = &image,
        .affineAnims = iconTemplate->affineAnims,
        .callback = iconTemplate->callback,
    };

    spriteId = CreateSprite(&spriteTemplate, x, y, subpriority);
    gSprites[spriteId].animPaused = TRUE;
    gSprites[spriteId].animBeginning = FALSE;
    gSprites[spriteId].images = (const struct SpriteFrameImage *)iconTemplate->image;
    return spriteId;
}

void sub_80D328C(struct Sprite *sprite)
{
    struct SpriteFrameImage image = { NULL, sSpriteImageSizes[sprite->oam.shape][sprite->oam.size] };
    sprite->images = &image;
    DestroySprite(sprite);
}

void SetPartyHPBarSprite(struct Sprite *sprite, u8 animNum)
{
    sprite->animNum = animNum;
    sprite->animDelayCounter = 0;
    sprite->animCmdIndex = 0;
}
