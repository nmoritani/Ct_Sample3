#ifndef _CT_MENU_BUTTON_ID_H_
#define _CT_MENU_BUTTON_ID_H_


typedef enum CtMenuButtonId{
    MenuButtonId_1      = 1,    ///MENU
    MenuButtonId_2      ,       ///THUMBNAIL
    MenuButtonId_3      ,       ///PLAYBACK
    MenuButtonId_4      ,       ///CLIP SEL
    MenuButtonId_5      ,       ///ALL SLOT
    MenuButtonId_6      ,       ///SLOT1
    MenuButtonId_7      ,       ///SLOT2
    MenuButtonId_8      ,       ///SAME FORMAT
    MenuButtonId_9      ,       ///MARKED
    MenuButtonId_10     ,       ///TEXT MEMO
    MenuButtonId_11     ,       ///RESUME PLAY
    MenuButtonId_12     ,       ///ON
    MenuButtonId_13     ,       ///OFF
    MenuButtonId_14     ,       ///SEEK POS SEL
    MenuButtonId_15     ,       ///CLIP
    MenuButtonId_16     ,       ///CLIP&TEXT MEMO
    MenuButtonId_17     ,       ///CLIP
    MenuButtonId_18     ,       ///PROTECT
    MenuButtonId_19     ,       ///SELECT
    MenuButtonId_20     ,       ///DELET
    MenuButtonId_21     ,       ///ALL
    MenuButtonId_22     ,       ///SELECT
    MenuButtonId_23     ,       ///COPY
    MenuButtonId_24     ,       ///ALL
    MenuButtonId_25     ,       ///SLOT1->SLOT2
    MenuButtonId_26     ,       ///SLOT2->SLOT1
    MenuButtonId_27     ,       ///ALL SLOT->FTP
    MenuButtonId_28     ,       ///SELECT
    MenuButtonId_29     ,       ///SLOT1->SLOT2
    MenuButtonId_30     ,       ///SLOT2->SLOT1
    MenuButtonId_31     ,       ///ALL SLOT->FTP
    MenuButtonId_32     ,       ///REPAIR
    MenuButtonId_33     ,       ///YES
    MenuButtonId_34     ,       ///NO
    MenuButtonId_35     ,       ///RE-CONNECT
    MenuButtonId_36     ,       ///SELECT
    MenuButtonId_37     ,       ///INFORMATION
    MenuButtonId_38     ,       ///DISPLAY
    MenuButtonId_39     ,       ///INDICATOR
    MenuButtonId_40     ,       ///ALL HIDE
    MenuButtonId_41     ,       ///MARKER
    MenuButtonId_42     ,       ///TEXT MEMO
    MenuButtonId_43     ,       ///PROXY
    MenuButtonId_44     ,       ///TEXT MEMO IND.
    MenuButtonId_45     ,       ///ALL
    MenuButtonId_46     ,       ///HIDE CARD SERIAL
    MenuButtonId_47     ,       ///DATA
    MenuButtonId_48     ,       ///START TC
    MenuButtonId_49     ,       ///CLIP NAME
    MenuButtonId_50     ,       ///CAMERA
    MenuButtonId_51     ,       ///SW MODE
    MenuButtonId_52     ,       ///LOW GAIN
    MenuButtonId_53     ,       ///MID GAIN
    MenuButtonId_54     ,       ///HIGH GAIN
    MenuButtonId_55     ,       ///SUPER GAIN
    MenuButtonId_56     ,       ///24dB
    MenuButtonId_57     ,       ///30dB
    MenuButtonId_58     ,       ///36dB
    MenuButtonId_59     ,       ///ALL
    MenuButtonId_60     ,       ///O.I.S.
    MenuButtonId_61     ,       ///ON
    MenuButtonId_62     ,       ///OFF
    MenuButtonId_63     ,       ///HYBRID O.I.S.
    MenuButtonId_64     ,       ///ON
    MenuButtonId_65     ,       ///OFF
    MenuButtonId_66     ,       ///O.I.S. MODE
    MenuButtonId_67     ,       ///NORMAL
    MenuButtonId_68     ,       ///PAN/TILT
    MenuButtonId_69     ,       ///STABLE
    MenuButtonId_70     ,       ///ATW
    MenuButtonId_71     ,       ///Ach
    MenuButtonId_72     ,       ///Bch
    MenuButtonId_73     ,       ///PRE
    MenuButtonId_74     ,       ///OFF
    MenuButtonId_75     ,       ///ATW SPEED
    MenuButtonId_76     ,       ///FAST
    MenuButtonId_77     ,       ///NORMAL
    MenuButtonId_78     ,       ///SLOW
    MenuButtonId_79     ,       ///ATW TARGET R
    MenuButtonId_80     ,       ///ATW TARGET B
    MenuButtonId_81     ,       ///W.BAL PRESET
    MenuButtonId_82     ,       ///3200K
    MenuButtonId_83     ,       ///5600K
    MenuButtonId_84     ,       ///VAR
    MenuButtonId_85     ,       ///W.BAL VAR
    MenuButtonId_86     ,       ///H.ZOOM SPEED
    MenuButtonId_87     ,       ///I.ZOOM
    MenuButtonId_88     ,       ///ON
    MenuButtonId_89     ,       ///OFF
    MenuButtonId_90     ,       ///PUSH AF MODE
    MenuButtonId_91     ,       ///TURBO
    MenuButtonId_92     ,       ///NORMAL
    MenuButtonId_93     ,       ///MF ASSIST
    MenuButtonId_94     ,       ///ON
    MenuButtonId_95     ,       ///OFF
    MenuButtonId_96     ,       ///MACRO
    MenuButtonId_97     ,       ///ON
    MenuButtonId_98     ,       ///OFF
    MenuButtonId_99     ,       ///MACRO MODE
    MenuButtonId_100    ,       ///WIDE
    MenuButtonId_101    ,       ///ALL
    MenuButtonId_102    ,       ///AF SPEED
    MenuButtonId_103    ,       ///AF AREA WIDTH
    MenuButtonId_104    ,       ///ON
    MenuButtonId_105    ,       ///OFF
    MenuButtonId_106    ,       ///A.IRIS SPEED
    MenuButtonId_107    ,       ///FAST
    MenuButtonId_108    ,       ///NORMAL
    MenuButtonId_109    ,       ///SLOW
    MenuButtonId_110    ,       ///A.IRIS WINDOW
    MenuButtonId_111    ,       ///NORMAL1
    MenuButtonId_112    ,       ///NORMAL2
    MenuButtonId_113    ,       ///CENTER
    MenuButtonId_114    ,       ///AREA MODE
    MenuButtonId_115    ,       ///INHIBIT
    MenuButtonId_116    ,       ///FOCUS
    MenuButtonId_117    ,       ///IRIS
    MenuButtonId_118    ,       ///Y GET
    MenuButtonId_119    ,       ///FOCUS/IRIS
    MenuButtonId_120    ,       ///FOCUS/Y GET
    MenuButtonId_121    ,       ///ZOOM/FOCUS
    MenuButtonId_122    ,       ///IP REMOTE
    MenuButtonId_123    ,       ///CAMERA
    MenuButtonId_124    ,       ///IR REC
    MenuButtonId_125    ,       ///ON
    MenuButtonId_126    ,       ///OFF
    MenuButtonId_127    ,       ///AUTO SW
    MenuButtonId_128    ,       ///A.IRIS
    MenuButtonId_129    ,       ///ON
    MenuButtonId_130    ,       ///OFF
    MenuButtonId_131    ,       ///AGC
    MenuButtonId_132    ,       ///ON
    MenuButtonId_133    ,       ///OFF
    MenuButtonId_134    ,       ///AGC LIMIT
    MenuButtonId_135    ,       ///3dB
    MenuButtonId_136    ,       ///6dB
    MenuButtonId_137    ,       ///12dB
    MenuButtonId_138    ,       ///18dB
    MenuButtonId_139    ,       ///AGC POINT
    MenuButtonId_140    ,       ///F4.0
    MenuButtonId_141    ,       ///F5.6
    MenuButtonId_142    ,       ///A.SHUTTER
    MenuButtonId_143    ,       ///ON
    MenuButtonId_144    ,       ///OFF
    MenuButtonId_145    ,       ///A.SHUTTER LIMIT
    MenuButtonId_146    ,       ///1/100
    MenuButtonId_147    ,       ///1/120
    MenuButtonId_148    ,       ///1/250
    MenuButtonId_149    ,       ///A.SHUTTER POINT
    MenuButtonId_150    ,       ///F8.0
    MenuButtonId_151    ,       ///F9.6
    MenuButtonId_152    ,       ///ATW
    MenuButtonId_153    ,       ///ON
    MenuButtonId_154    ,       ///OFF
    MenuButtonId_155    ,       ///AF
    MenuButtonId_156    ,       ///ON
    MenuButtonId_157    ,       ///OFF
    MenuButtonId_158    ,       ///USER SW
    MenuButtonId_159    ,       ///USER1
    MenuButtonId_160    ,       ///INHIBIT
    MenuButtonId_161    ,       ///AWB
    MenuButtonId_162    ,       ///DRS
    MenuButtonId_163    ,       ///FBC
    MenuButtonId_164    ,       ///ONE PUSH AF
    MenuButtonId_165    ,       ///S.GAIN
    MenuButtonId_166    ,       ///AREA
    MenuButtonId_167    ,       ///AF AREA
    MenuButtonId_168    ,       ///ATW
    MenuButtonId_169    ,       ///ATW LOCK
    MenuButtonId_170    ,       ///SPOTLIGHT
    MenuButtonId_171    ,       ///BACKLIGHT
    MenuButtonId_172    ,       ///A.IRIS LEVEL
    MenuButtonId_173    ,       ///IRIS
    MenuButtonId_174    ,       ///Y GET
    MenuButtonId_175    ,       ///FOCUS MACRO
    MenuButtonId_176    ,       ///O.I.S.
    MenuButtonId_177    ,       ///i.ZOOM
    MenuButtonId_178    ,       ///D.ZOOM
    MenuButtonId_179    ,       ///IR REC
    MenuButtonId_180    ,       ///FAST ZOOM
    MenuButtonId_181    ,       ///PRE REC
    MenuButtonId_182    ,       ///VFR
    MenuButtonId_183    ,       ///SUPER SLOW
    MenuButtonId_184    ,       ///REC CHECK
    MenuButtonId_185    ,       ///BACKGR PAUSE
    MenuButtonId_186    ,       ///DEL LAST CLIP
    MenuButtonId_187    ,       ///SLOT SEL
    MenuButtonId_188    ,       ///TEXT MEMO
    MenuButtonId_189    ,       ///SHOT MARK
    MenuButtonId_190    ,       ///EXPAND
    MenuButtonId_191    ,       ///PEAKING
    MenuButtonId_192    ,       ///WFM
    MenuButtonId_193    ,       ///ZEBRA
    MenuButtonId_194    ,       ///LEVEL GAUGE
    MenuButtonId_195    ,       ///LEVEL GAUGE SET
    MenuButtonId_196    ,       ///LCD/VF HDR
    MenuButtonId_197    ,       ///VF ON/OFF
    MenuButtonId_198    ,       ///LCD/VF DETAIL
    MenuButtonId_199    ,       ///AUDIO MON SEL
    MenuButtonId_200    ,       ///MENU
    MenuButtonId_201    ,       ///LOAD SETUP FILE
    MenuButtonId_202    ,       ///LCD BACKLIGHT
    MenuButtonId_203    ,       ///CARD READER MODE
    MenuButtonId_204    ,       ///NETWORK FUNC
    MenuButtonId_205    ,       ///STREAMING START
    MenuButtonId_206    ,       ///REC DURING UPLOAD
    MenuButtonId_207    ,       ///UPLOAD LIST
    MenuButtonId_208    ,       ///USER2
    MenuButtonId_209    ,       ///INHIBIT
    MenuButtonId_210    ,       ///AWB
    MenuButtonId_211    ,       ///DRS
    MenuButtonId_212    ,       ///FBC
    MenuButtonId_213    ,       ///ONE PUSH AF
    MenuButtonId_214    ,       ///S.GAIN
    MenuButtonId_215    ,       ///AREA
    MenuButtonId_216    ,       ///AF AREA
    MenuButtonId_217    ,       ///ATW
    MenuButtonId_218    ,       ///ATW LOCK
    MenuButtonId_219    ,       ///SPOTLIGHT
    MenuButtonId_220    ,       ///BACKLIGHT
    MenuButtonId_221    ,       ///A.IRIS LEVEL
    MenuButtonId_222    ,       ///IRIS
    MenuButtonId_223    ,       ///Y GET
    MenuButtonId_224    ,       ///FOCUS MACRO
    MenuButtonId_225    ,       ///O.I.S.
    MenuButtonId_226    ,       ///i.ZOOM
    MenuButtonId_227    ,       ///D.ZOOM
    MenuButtonId_228    ,       ///IR REC
    MenuButtonId_229    ,       ///FAST ZOOM
    MenuButtonId_230    ,       ///PRE REC
    MenuButtonId_231    ,       ///VFR
    MenuButtonId_232    ,       ///SUPER SLOW
    MenuButtonId_233    ,       ///REC CHECK
    MenuButtonId_234    ,       ///BACKGR PAUSE
    MenuButtonId_235    ,       ///DEL LAST CLIP
    MenuButtonId_236    ,       ///SLOT SEL
    MenuButtonId_237    ,       ///TEXT MEMO
    MenuButtonId_238    ,       ///SHOT MARK
    MenuButtonId_239    ,       ///EXPAND
    MenuButtonId_240    ,       ///PEAKING
    MenuButtonId_241    ,       ///WFM
    MenuButtonId_242    ,       ///ZEBRA
    MenuButtonId_243    ,       ///LEVEL GAUGE
    MenuButtonId_244    ,       ///LEVEL GAUGE SET
    MenuButtonId_245    ,       ///LCD/VF HDR
    MenuButtonId_246    ,       ///VF ON/OFF
    MenuButtonId_247    ,       ///LCD/VF DETAIL
    MenuButtonId_248    ,       ///AUDIO MON SEL
    MenuButtonId_249    ,       ///MENU
    MenuButtonId_250    ,       ///LOAD SETUP FILE
    MenuButtonId_251    ,       ///LCD BACKLIGHT
    MenuButtonId_252    ,       ///CARD READER MODE
    MenuButtonId_253    ,       ///NETWORK FUNC
    MenuButtonId_254    ,       ///STREAMING START
    MenuButtonId_255    ,       ///REC DURING UPLOAD
    MenuButtonId_256    ,       ///UPLOAD LIST
    MenuButtonId_257    ,       ///USER3
    MenuButtonId_258    ,       ///INHIBIT
    MenuButtonId_259    ,       ///AWB
    MenuButtonId_260    ,       ///DRS
    MenuButtonId_261    ,       ///FBC
    MenuButtonId_262    ,       ///ONE PUSH AF
    MenuButtonId_263    ,       ///S.GAIN
    MenuButtonId_264    ,       ///AREA
    MenuButtonId_265    ,       ///AF AREA
    MenuButtonId_266    ,       ///ATW
    MenuButtonId_267    ,       ///ATW LOCK
    MenuButtonId_268    ,       ///SPOTLIGHT
    MenuButtonId_269    ,       ///BACKLIGHT
    MenuButtonId_270    ,       ///A.IRIS LEVEL
    MenuButtonId_271    ,       ///IRIS
    MenuButtonId_272    ,       ///Y GET
    MenuButtonId_273    ,       ///FOCUS MACRO
    MenuButtonId_274    ,       ///O.I.S.
    MenuButtonId_275    ,       ///i.ZOOM
    MenuButtonId_276    ,       ///D.ZOOM
    MenuButtonId_277    ,       ///IR REC
    MenuButtonId_278    ,       ///FAST ZOOM
    MenuButtonId_279    ,       ///PRE REC
    MenuButtonId_280    ,       ///VFR
    MenuButtonId_281    ,       ///SUPER SLOW
    MenuButtonId_282    ,       ///REC CHECK
    MenuButtonId_283    ,       ///BACKGR PAUSE
    MenuButtonId_284    ,       ///DEL LAST CLIP
    MenuButtonId_285    ,       ///SLOT SEL
    MenuButtonId_286    ,       ///TEXT MEMO
    MenuButtonId_287    ,       ///SHOT MARK
    MenuButtonId_288    ,       ///EXPAND
    MenuButtonId_289    ,       ///PEAKING
    MenuButtonId_290    ,       ///WFM
    MenuButtonId_291    ,       ///ZEBRA
    MenuButtonId_292    ,       ///LEVEL GAUGE
    MenuButtonId_293    ,       ///LEVEL GAUGE SET
    MenuButtonId_294    ,       ///LCD/VF HDR
    MenuButtonId_295    ,       ///VF ON/OFF
    MenuButtonId_296    ,       ///LCD/VF DETAIL
    MenuButtonId_297    ,       ///AUDIO MON SEL
    MenuButtonId_298    ,       ///MENU
    MenuButtonId_299    ,       ///LOAD SETUP FILE
    MenuButtonId_300    ,       ///LCD BACKLIGHT
    MenuButtonId_301    ,       ///CARD READER MODE
    MenuButtonId_302    ,       ///NETWORK FUNC
    MenuButtonId_303    ,       ///STREAMING START
    MenuButtonId_304    ,       ///REC DURING UPLOAD
    MenuButtonId_305    ,       ///UPLOAD LIST
    MenuButtonId_306    ,       ///USER4
    MenuButtonId_307    ,       ///INHIBIT
    MenuButtonId_308    ,       ///AWB
    MenuButtonId_309    ,       ///DRS
    MenuButtonId_310    ,       ///FBC
    MenuButtonId_311    ,       ///ONE PUSH AF
    MenuButtonId_312    ,       ///S.GAIN
    MenuButtonId_313    ,       ///AREA
    MenuButtonId_314    ,       ///AF AREA
    MenuButtonId_315    ,       ///ATW
    MenuButtonId_316    ,       ///ATW LOCK
    MenuButtonId_317    ,       ///SPOTLIGHT
    MenuButtonId_318    ,       ///BACKLIGHT
    MenuButtonId_319    ,       ///A.IRIS LEVEL
    MenuButtonId_320    ,       ///IRIS
    MenuButtonId_321    ,       ///Y GET
    MenuButtonId_322    ,       ///FOCUS MACRO
    MenuButtonId_323    ,       ///O.I.S.
    MenuButtonId_324    ,       ///i.ZOOM
    MenuButtonId_325    ,       ///D.ZOOM
    MenuButtonId_326    ,       ///IR REC
    MenuButtonId_327    ,       ///FAST ZOOM
    MenuButtonId_328    ,       ///PRE REC
    MenuButtonId_329    ,       ///VFR
    MenuButtonId_330    ,       ///SUPER SLOW
    MenuButtonId_331    ,       ///REC CHECK
    MenuButtonId_332    ,       ///BACKGR PAUSE
    MenuButtonId_333    ,       ///DEL LAST CLIP
    MenuButtonId_334    ,       ///SLOT SEL
    MenuButtonId_335    ,       ///TEXT MEMO
    MenuButtonId_336    ,       ///SHOT MARK
    MenuButtonId_337    ,       ///EXPAND
    MenuButtonId_338    ,       ///PEAKING
    MenuButtonId_339    ,       ///WFM
    MenuButtonId_340    ,       ///ZEBRA
    MenuButtonId_341    ,       ///LEVEL GAUGE
    MenuButtonId_342    ,       ///LEVEL GAUGE SET
    MenuButtonId_343    ,       ///LCD/VF HDR
    MenuButtonId_344    ,       ///VF ON/OFF
    MenuButtonId_345    ,       ///LCD/VF DETAIL
    MenuButtonId_346    ,       ///AUDIO MON SEL
    MenuButtonId_347    ,       ///MENU
    MenuButtonId_348    ,       ///LOAD SETUP FILE
    MenuButtonId_349    ,       ///LCD BACKLIGHT
    MenuButtonId_350    ,       ///CARD READER MODE
    MenuButtonId_351    ,       ///NETWORK FUNC
    MenuButtonId_352    ,       ///STREAMING START
    MenuButtonId_353    ,       ///REC DURING UPLOAD
    MenuButtonId_354    ,       ///UPLOAD LIST
    MenuButtonId_355    ,       ///USER5
    MenuButtonId_356    ,       ///INHIBIT
    MenuButtonId_357    ,       ///AWB
    MenuButtonId_358    ,       ///DRS
    MenuButtonId_359    ,       ///FBC
    MenuButtonId_360    ,       ///ONE PUSH AF
    MenuButtonId_361    ,       ///S.GAIN
    MenuButtonId_362    ,       ///AREA
    MenuButtonId_363    ,       ///AF AREA
    MenuButtonId_364    ,       ///ATW
    MenuButtonId_365    ,       ///ATW LOCK
    MenuButtonId_366    ,       ///SPOTLIGHT
    MenuButtonId_367    ,       ///BACKLIGHT
    MenuButtonId_368    ,       ///A.IRIS LEVEL
    MenuButtonId_369    ,       ///IRIS
    MenuButtonId_370    ,       ///Y GET
    MenuButtonId_371    ,       ///FOCUS MACRO
    MenuButtonId_372    ,       ///O.I.S.
    MenuButtonId_373    ,       ///i.ZOOM
    MenuButtonId_374    ,       ///D.ZOOM
    MenuButtonId_375    ,       ///IR REC
    MenuButtonId_376    ,       ///FAST ZOOM
    MenuButtonId_377    ,       ///PRE REC
    MenuButtonId_378    ,       ///VFR
    MenuButtonId_379    ,       ///SUPER SLOW
    MenuButtonId_380    ,       ///REC CHECK
    MenuButtonId_381    ,       ///BACKGR PAUSE
    MenuButtonId_382    ,       ///DEL LAST CLIP
    MenuButtonId_383    ,       ///SLOT SEL
    MenuButtonId_384    ,       ///TEXT MEMO
    MenuButtonId_385    ,       ///SHOT MARK
    MenuButtonId_386    ,       ///EXPAND
    MenuButtonId_387    ,       ///PEAKING
    MenuButtonId_388    ,       ///WFM
    MenuButtonId_389    ,       ///ZEBRA
    MenuButtonId_390    ,       ///LEVEL GAUGE
    MenuButtonId_391    ,       ///LEVEL GAUGE SET
    MenuButtonId_392    ,       ///LCD/VF HDR
    MenuButtonId_393    ,       ///VF ON/OFF
    MenuButtonId_394    ,       ///LCD/VF DETAIL
    MenuButtonId_395    ,       ///AUDIO MON SEL
    MenuButtonId_396    ,       ///MENU
    MenuButtonId_397    ,       ///LOAD SETUP FILE
    MenuButtonId_398    ,       ///LCD BACKLIGHT
    MenuButtonId_399    ,       ///CARD READER MODE
    MenuButtonId_400    ,       ///NETWORK FUNC
    MenuButtonId_401    ,       ///STREAMING START
    MenuButtonId_402    ,       ///REC DURING UPLOAD
    MenuButtonId_403    ,       ///UPLOAD LIST
    MenuButtonId_404    ,       ///USER6
    MenuButtonId_405    ,       ///INHIBIT
    MenuButtonId_406    ,       ///AWB
    MenuButtonId_407    ,       ///DRS
    MenuButtonId_408    ,       ///FBC
    MenuButtonId_409    ,       ///ONE PUSH AF
    MenuButtonId_410    ,       ///S.GAIN
    MenuButtonId_411    ,       ///AREA
    MenuButtonId_412    ,       ///AF AREA
    MenuButtonId_413    ,       ///ATW
    MenuButtonId_414    ,       ///ATW LOCK
    MenuButtonId_415    ,       ///SPOTLIGHT
    MenuButtonId_416    ,       ///BACKLIGHT
    MenuButtonId_417    ,       ///A.IRIS LEVEL
    MenuButtonId_418    ,       ///IRIS
    MenuButtonId_419    ,       ///Y GET
    MenuButtonId_420    ,       ///FOCUS MACRO
    MenuButtonId_421    ,       ///O.I.S.
    MenuButtonId_422    ,       ///i.ZOOM
    MenuButtonId_423    ,       ///D.ZOOM
    MenuButtonId_424    ,       ///IR REC
    MenuButtonId_425    ,       ///FAST ZOOM
    MenuButtonId_426    ,       ///PRE REC
    MenuButtonId_427    ,       ///VFR
    MenuButtonId_428    ,       ///SUPER SLOW
    MenuButtonId_429    ,       ///REC CHECK
    MenuButtonId_430    ,       ///BACKGR PAUSE
    MenuButtonId_431    ,       ///DEL LAST CLIP
    MenuButtonId_432    ,       ///SLOT SEL
    MenuButtonId_433    ,       ///TEXT MEMO
    MenuButtonId_434    ,       ///SHOT MARK
    MenuButtonId_435    ,       ///EXPAND
    MenuButtonId_436    ,       ///PEAKING
    MenuButtonId_437    ,       ///WFM
    MenuButtonId_438    ,       ///ZEBRA
    MenuButtonId_439    ,       ///LEVEL GAUGE
    MenuButtonId_440    ,       ///LEVEL GAUGE SET
    MenuButtonId_441    ,       ///LCD/VF HDR
    MenuButtonId_442    ,       ///VF ON/OFF
    MenuButtonId_443    ,       ///LCD/VF DETAIL
    MenuButtonId_444    ,       ///AUDIO MON SEL
    MenuButtonId_445    ,       ///MENU
    MenuButtonId_446    ,       ///LOAD SETUP FILE
    MenuButtonId_447    ,       ///LCD BACKLIGHT
    MenuButtonId_448    ,       ///CARD READER MODE
    MenuButtonId_449    ,       ///NETWORK FUNC
    MenuButtonId_450    ,       ///STREAMING START
    MenuButtonId_451    ,       ///REC DURING UPLOAD
    MenuButtonId_452    ,       ///UPLOAD LIST
    MenuButtonId_453    ,       ///USER7
    MenuButtonId_454    ,       ///INHIBIT
    MenuButtonId_455    ,       ///AWB
    MenuButtonId_456    ,       ///DRS
    MenuButtonId_457    ,       ///FBC
    MenuButtonId_458    ,       ///ONE PUSH AF
    MenuButtonId_459    ,       ///S.GAIN
    MenuButtonId_460    ,       ///AREA
    MenuButtonId_461    ,       ///AF AREA
    MenuButtonId_462    ,       ///ATW
    MenuButtonId_463    ,       ///ATW LOCK
    MenuButtonId_464    ,       ///SPOTLIGHT
    MenuButtonId_465    ,       ///BACKLIGHT
    MenuButtonId_466    ,       ///A.IRIS LEVEL
    MenuButtonId_467    ,       ///IRIS
    MenuButtonId_468    ,       ///Y GET
    MenuButtonId_469    ,       ///FOCUS MACRO
    MenuButtonId_470    ,       ///O.I.S.
    MenuButtonId_471    ,       ///i.ZOOM
    MenuButtonId_472    ,       ///D.ZOOM
    MenuButtonId_473    ,       ///IR REC
    MenuButtonId_474    ,       ///FAST ZOOM
    MenuButtonId_475    ,       ///PRE REC
    MenuButtonId_476    ,       ///VFR
    MenuButtonId_477    ,       ///SUPER SLOW
    MenuButtonId_478    ,       ///REC CHECK
    MenuButtonId_479    ,       ///BACKGR PAUSE
    MenuButtonId_480    ,       ///DEL LAST CLIP
    MenuButtonId_481    ,       ///SLOT SEL
    MenuButtonId_482    ,       ///TEXT MEMO
    MenuButtonId_483    ,       ///SHOT MARK
    MenuButtonId_484    ,       ///EXPAND
    MenuButtonId_485    ,       ///PEAKING
    MenuButtonId_486    ,       ///WFM
    MenuButtonId_487    ,       ///ZEBRA
    MenuButtonId_488    ,       ///LEVEL GAUGE
    MenuButtonId_489    ,       ///LEVEL GAUGE SET
    MenuButtonId_490    ,       ///LCD/VF HDR
    MenuButtonId_491    ,       ///VF ON/OFF
    MenuButtonId_492    ,       ///LCD/VF DETAIL
    MenuButtonId_493    ,       ///AUDIO MON SEL
    MenuButtonId_494    ,       ///MENU
    MenuButtonId_495    ,       ///LOAD SETUP FILE
    MenuButtonId_496    ,       ///LCD BACKLIGHT
    MenuButtonId_497    ,       ///CARD READER MODE
    MenuButtonId_498    ,       ///NETWORK FUNC
    MenuButtonId_499    ,       ///STREAMING START
    MenuButtonId_500    ,       ///REC DURING UPLOAD
    MenuButtonId_501    ,       ///UPLOAD LIST
    MenuButtonId_502    ,       ///USER8
    MenuButtonId_503    ,       ///INHIBIT
    MenuButtonId_504    ,       ///AWB
    MenuButtonId_505    ,       ///DRS
    MenuButtonId_506    ,       ///FBC
    MenuButtonId_507    ,       ///ONE PUSH AF
    MenuButtonId_508    ,       ///S.GAIN
    MenuButtonId_509    ,       ///AREA
    MenuButtonId_510    ,       ///AF AREA
    MenuButtonId_511    ,       ///ATW
    MenuButtonId_512    ,       ///ATW LOCK
    MenuButtonId_513    ,       ///SPOTLIGHT
    MenuButtonId_514    ,       ///BACKLIGHT
    MenuButtonId_515    ,       ///A.IRIS LEVEL
    MenuButtonId_516    ,       ///IRIS
    MenuButtonId_517    ,       ///Y GET
    MenuButtonId_518    ,       ///FOCUS MACRO
    MenuButtonId_519    ,       ///O.I.S.
    MenuButtonId_520    ,       ///i.ZOOM
    MenuButtonId_521    ,       ///D.ZOOM
    MenuButtonId_522    ,       ///IR REC
    MenuButtonId_523    ,       ///FAST ZOOM
    MenuButtonId_524    ,       ///PRE REC
    MenuButtonId_525    ,       ///VFR
    MenuButtonId_526    ,       ///SUPER SLOW
    MenuButtonId_527    ,       ///REC CHECK
    MenuButtonId_528    ,       ///BACKGR PAUSE
    MenuButtonId_529    ,       ///DEL LAST CLIP
    MenuButtonId_530    ,       ///SLOT SEL
    MenuButtonId_531    ,       ///TEXT MEMO
    MenuButtonId_532    ,       ///SHOT MARK
    MenuButtonId_533    ,       ///EXPAND
    MenuButtonId_534    ,       ///PEAKING
    MenuButtonId_535    ,       ///WFM
    MenuButtonId_536    ,       ///ZEBRA
    MenuButtonId_537    ,       ///LEVEL GAUGE
    MenuButtonId_538    ,       ///LEVEL GAUGE SET
    MenuButtonId_539    ,       ///LCD/VF HDR
    MenuButtonId_540    ,       ///VF ON/OFF
    MenuButtonId_541    ,       ///LCD/VF DETAIL
    MenuButtonId_542    ,       ///AUDIO MON SEL
    MenuButtonId_543    ,       ///MENU
    MenuButtonId_544    ,       ///LOAD SETUP FILE
    MenuButtonId_545    ,       ///LCD BACKLIGHT
    MenuButtonId_546    ,       ///CARD READER MODE
    MenuButtonId_547    ,       ///NETWORK FUNC
    MenuButtonId_548    ,       ///STREAMING START
    MenuButtonId_549    ,       ///REC DURING UPLOAD
    MenuButtonId_550    ,       ///UPLOAD LIST
    MenuButtonId_551    ,       ///USER9
    MenuButtonId_552    ,       ///INHIBIT
    MenuButtonId_553    ,       ///AWB
    MenuButtonId_554    ,       ///DRS
    MenuButtonId_555    ,       ///FBC
    MenuButtonId_556    ,       ///ONE PUSH AF
    MenuButtonId_557    ,       ///S.GAIN
    MenuButtonId_558    ,       ///AREA
    MenuButtonId_559    ,       ///AF AREA
    MenuButtonId_560    ,       ///ATW
    MenuButtonId_561    ,       ///ATW LOCK
    MenuButtonId_562    ,       ///SPOTLIGHT
    MenuButtonId_563    ,       ///BACKLIGHT
    MenuButtonId_564    ,       ///A.IRIS LEVEL
    MenuButtonId_565    ,       ///IRIS
    MenuButtonId_566    ,       ///Y GET
    MenuButtonId_567    ,       ///FOCUS MACRO
    MenuButtonId_568    ,       ///O.I.S.
    MenuButtonId_569    ,       ///i.ZOOM
    MenuButtonId_570    ,       ///D.ZOOM
    MenuButtonId_571    ,       ///IR REC
    MenuButtonId_572    ,       ///FAST ZOOM
    MenuButtonId_573    ,       ///PRE REC
    MenuButtonId_574    ,       ///VFR
    MenuButtonId_575    ,       ///SUPER SLOW
    MenuButtonId_576    ,       ///REC CHECK
    MenuButtonId_577    ,       ///BACKGR PAUSE
    MenuButtonId_578    ,       ///DEL LAST CLIP
    MenuButtonId_579    ,       ///SLOT SEL
    MenuButtonId_580    ,       ///TEXT MEMO
    MenuButtonId_581    ,       ///SHOT MARK
    MenuButtonId_582    ,       ///EXPAND
    MenuButtonId_583    ,       ///PEAKING
    MenuButtonId_584    ,       ///WFM
    MenuButtonId_585    ,       ///ZEBRA
    MenuButtonId_586    ,       ///LEVEL GAUGE
    MenuButtonId_587    ,       ///LEVEL GAUGE SET
    MenuButtonId_588    ,       ///LCD/VF HDR
    MenuButtonId_589    ,       ///VF ON/OFF
    MenuButtonId_590    ,       ///LCD/VF DETAIL
    MenuButtonId_591    ,       ///AUDIO MON SEL
    MenuButtonId_592    ,       ///MENU
    MenuButtonId_593    ,       ///LOAD SETUP FILE
    MenuButtonId_594    ,       ///LCD BACKLIGHT
    MenuButtonId_595    ,       ///CARD READER MODE
    MenuButtonId_596    ,       ///NETWORK FUNC
    MenuButtonId_597    ,       ///STREAMING START
    MenuButtonId_598    ,       ///REC DURING UPLOAD
    MenuButtonId_599    ,       ///UPLOAD LIST
    MenuButtonId_600    ,       ///USER10
    MenuButtonId_601    ,       ///INHIBIT
    MenuButtonId_602    ,       ///AWB
    MenuButtonId_603    ,       ///DRS
    MenuButtonId_604    ,       ///FBC
    MenuButtonId_605    ,       ///ONE PUSH AF
    MenuButtonId_606    ,       ///S.GAIN
    MenuButtonId_607    ,       ///AREA
    MenuButtonId_608    ,       ///AF AREA
    MenuButtonId_609    ,       ///ATW
    MenuButtonId_610    ,       ///ATW LOCK
    MenuButtonId_611    ,       ///SPOTLIGHT
    MenuButtonId_612    ,       ///BACKLIGHT
    MenuButtonId_613    ,       ///A.IRIS LEVEL
    MenuButtonId_614    ,       ///IRIS
    MenuButtonId_615    ,       ///Y GET
    MenuButtonId_616    ,       ///FOCUS MACRO
    MenuButtonId_617    ,       ///O.I.S.
    MenuButtonId_618    ,       ///i.ZOOM
    MenuButtonId_619    ,       ///D.ZOOM
    MenuButtonId_620    ,       ///IR REC
    MenuButtonId_621    ,       ///FAST ZOOM
    MenuButtonId_622    ,       ///PRE REC
    MenuButtonId_623    ,       ///VFR
    MenuButtonId_624    ,       ///SUPER SLOW
    MenuButtonId_625    ,       ///REC CHECK
    MenuButtonId_626    ,       ///BACKGR PAUSE
    MenuButtonId_627    ,       ///DEL LAST CLIP
    MenuButtonId_628    ,       ///SLOT SEL
    MenuButtonId_629    ,       ///TEXT MEMO
    MenuButtonId_630    ,       ///SHOT MARK
    MenuButtonId_631    ,       ///EXPAND
    MenuButtonId_632    ,       ///PEAKING
    MenuButtonId_633    ,       ///WFM
    MenuButtonId_634    ,       ///ZEBRA
    MenuButtonId_635    ,       ///LEVEL GAUGE
    MenuButtonId_636    ,       ///LEVEL GAUGE SET
    MenuButtonId_637    ,       ///LCD/VF HDR
    MenuButtonId_638    ,       ///VF ON/OFF
    MenuButtonId_639    ,       ///LCD/VF DETAIL
    MenuButtonId_640    ,       ///AUDIO MON SEL
    MenuButtonId_641    ,       ///MENU
    MenuButtonId_642    ,       ///LOAD SETUP FILE
    MenuButtonId_643    ,       ///LCD BACKLIGHT
    MenuButtonId_644    ,       ///CARD READER MODE
    MenuButtonId_645    ,       ///NETWORK FUNC
    MenuButtonId_646    ,       ///STREAMING START
    MenuButtonId_647    ,       ///REC DURING UPLOAD
    MenuButtonId_648    ,       ///UPLOAD LIST
    MenuButtonId_649    ,       ///USER11
    MenuButtonId_650    ,       ///INHIBIT
    MenuButtonId_651    ,       ///AWB
    MenuButtonId_652    ,       ///DRS
    MenuButtonId_653    ,       ///FBC
    MenuButtonId_654    ,       ///ONE PUSH AF
    MenuButtonId_655    ,       ///S.GAIN
    MenuButtonId_656    ,       ///AREA
    MenuButtonId_657    ,       ///AF AREA
    MenuButtonId_658    ,       ///ATW
    MenuButtonId_659    ,       ///ATW LOCK
    MenuButtonId_660    ,       ///SPOTLIGHT
    MenuButtonId_661    ,       ///BACKLIGHT
    MenuButtonId_662    ,       ///A.IRIS LEVEL
    MenuButtonId_663    ,       ///IRIS
    MenuButtonId_664    ,       ///Y GET
    MenuButtonId_665    ,       ///FOCUS MACRO
    MenuButtonId_666    ,       ///O.I.S.
    MenuButtonId_667    ,       ///i.ZOOM
    MenuButtonId_668    ,       ///D.ZOOM
    MenuButtonId_669    ,       ///IR REC
    MenuButtonId_670    ,       ///FAST ZOOM
    MenuButtonId_671    ,       ///PRE REC
    MenuButtonId_672    ,       ///VFR
    MenuButtonId_673    ,       ///SUPER SLOW
    MenuButtonId_674    ,       ///REC CHECK
    MenuButtonId_675    ,       ///BACKGR PAUSE
    MenuButtonId_676    ,       ///DEL LAST CLIP
    MenuButtonId_677    ,       ///SLOT SEL
    MenuButtonId_678    ,       ///TEXT MEMO
    MenuButtonId_679    ,       ///SHOT MARK
    MenuButtonId_680    ,       ///EXPAND
    MenuButtonId_681    ,       ///PEAKING
    MenuButtonId_682    ,       ///WFM
    MenuButtonId_683    ,       ///ZEBRA
    MenuButtonId_684    ,       ///LEVEL GAUGE
    MenuButtonId_685    ,       ///LEVEL GAUGE SET
    MenuButtonId_686    ,       ///LCD/VF HDR
    MenuButtonId_687    ,       ///VF ON/OFF
    MenuButtonId_688    ,       ///LCD/VF DETAIL
    MenuButtonId_689    ,       ///AUDIO MON SEL
    MenuButtonId_690    ,       ///MENU
    MenuButtonId_691    ,       ///LOAD SETUP FILE
    MenuButtonId_692    ,       ///LCD BACKLIGHT
    MenuButtonId_693    ,       ///CARD READER MODE
    MenuButtonId_694    ,       ///NETWORK FUNC
    MenuButtonId_695    ,       ///STREAMING START
    MenuButtonId_696    ,       ///REC DURING UPLOAD
    MenuButtonId_697    ,       ///UPLOAD LIST
    MenuButtonId_698    ,       ///USER12
    MenuButtonId_699    ,       ///INHIBIT
    MenuButtonId_700    ,       ///AWB
    MenuButtonId_701    ,       ///DRS
    MenuButtonId_702    ,       ///FBC
    MenuButtonId_703    ,       ///ONE PUSH AF
    MenuButtonId_704    ,       ///S.GAIN
    MenuButtonId_705    ,       ///AREA
    MenuButtonId_706    ,       ///AF AREA
    MenuButtonId_707    ,       ///ATW
    MenuButtonId_708    ,       ///ATW LOCK
    MenuButtonId_709    ,       ///SPOTLIGHT
    MenuButtonId_710    ,       ///BACKLIGHT
    MenuButtonId_711    ,       ///A.IRIS LEVEL
    MenuButtonId_712    ,       ///IRIS
    MenuButtonId_713    ,       ///Y GET
    MenuButtonId_714    ,       ///FOCUS MACRO
    MenuButtonId_715    ,       ///O.I.S.
    MenuButtonId_716    ,       ///i.ZOOM
    MenuButtonId_717    ,       ///D.ZOOM
    MenuButtonId_718    ,       ///IR REC
    MenuButtonId_719    ,       ///FAST ZOOM
    MenuButtonId_720    ,       ///PRE REC
    MenuButtonId_721    ,       ///VFR
    MenuButtonId_722    ,       ///SUPER SLOW
    MenuButtonId_723    ,       ///REC CHECK
    MenuButtonId_724    ,       ///BACKGR PAUSE
    MenuButtonId_725    ,       ///DEL LAST CLIP
    MenuButtonId_726    ,       ///SLOT SEL
    MenuButtonId_727    ,       ///TEXT MEMO
    MenuButtonId_728    ,       ///SHOT MARK
    MenuButtonId_729    ,       ///EXPAND
    MenuButtonId_730    ,       ///PEAKING
    MenuButtonId_731    ,       ///WFM
    MenuButtonId_732    ,       ///ZEBRA
    MenuButtonId_733    ,       ///LEVEL GAUGE
    MenuButtonId_734    ,       ///LEVEL GAUGE SET
    MenuButtonId_735    ,       ///LCD/VF HDR
    MenuButtonId_736    ,       ///VF ON/OFF
    MenuButtonId_737    ,       ///LCD/VF DETAIL
    MenuButtonId_738    ,       ///AUDIO MON SEL
    MenuButtonId_739    ,       ///MENU
    MenuButtonId_740    ,       ///LOAD SETUP FILE
    MenuButtonId_741    ,       ///LCD BACKLIGHT
    MenuButtonId_742    ,       ///CARD READER MODE
    MenuButtonId_743    ,       ///NETWORK FUNC
    MenuButtonId_744    ,       ///STREAMING START
    MenuButtonId_745    ,       ///REC DURING UPLOAD
    MenuButtonId_746    ,       ///UPLOAD LIST
    MenuButtonId_747    ,       ///SCENE FILE
    MenuButtonId_748    ,       ///FILE SELECT
    MenuButtonId_749    ,       ///F1:%s
    MenuButtonId_750    ,       ///F2:%s
    MenuButtonId_751    ,       ///F3:%s
    MenuButtonId_752    ,       ///F4:%s
    MenuButtonId_753    ,       ///F5:%s
    MenuButtonId_754    ,       ///F6:%s
    MenuButtonId_755    ,       ///NAME EDIT
    MenuButtonId_756    ,       ///LOAD/SAVE/INITIALIZE
    MenuButtonId_757    ,       ///LOAD
    MenuButtonId_758    ,       ///SAVE
    MenuButtonId_759    ,       ///INITIALIZE
    MenuButtonId_760    ,       ///VFR
    MenuButtonId_761    ,       ///ON
    MenuButtonId_762    ,       ///OFF
    MenuButtonId_763    ,       ///FRAME RATE
    MenuButtonId_764    ,       ///SYNC SCAN TYPE
    MenuButtonId_765    ,       ///sec
    MenuButtonId_766    ,       ///deg
    MenuButtonId_767    ,       ///SYNCHRO SCAN
    MenuButtonId_768    ,       ///MASTER DTL
    MenuButtonId_769    ,       ///DTL CORING
    MenuButtonId_770    ,       ///DETAIL SETTING
    MenuButtonId_771    ,       ///DETAIL
    MenuButtonId_772    ,       ///ON
    MenuButtonId_773    ,       ///OFF
    MenuButtonId_774    ,       ///V.DTL LEVEL
    MenuButtonId_775    ,       ///DTL FREQ.
    MenuButtonId_776    ,       ///LEVEL DEPEND.
    MenuButtonId_777    ,       ///KNEE APE LVL
    MenuButtonId_778    ,       ///DTL GAIN(+)
    MenuButtonId_779    ,       ///DTL GAIN(-)
    MenuButtonId_780    ,       ///SKIN TONE DTL A
    MenuButtonId_781    ,       ///ON
    MenuButtonId_782    ,       ///OFF
    MenuButtonId_783    ,       ///SKIN TONE DTL B
    MenuButtonId_784    ,       ///ON
    MenuButtonId_785    ,       ///OFF
    MenuButtonId_786    ,       ///SKIN TONE DTL C
    MenuButtonId_787    ,       ///ON
    MenuButtonId_788    ,       ///OFF
    MenuButtonId_789    ,       ///SKIN TONE ZEBRA
    MenuButtonId_790    ,       ///ON
    MenuButtonId_791    ,       ///OFF
    MenuButtonId_792    ,       ///SKIN TONE DTL SETTING
    MenuButtonId_793    ,       ///DETECT TABLE
    MenuButtonId_794    ,       ///A
    MenuButtonId_795    ,       ///B
    MenuButtonId_796    ,       ///C
    MenuButtonId_797    ,       ///SKIN DTL EFFECT
    MenuButtonId_798    ,       ///I CENTER
    MenuButtonId_799    ,       ///I WIDTH
    MenuButtonId_800    ,       ///Q WIDTH
    MenuButtonId_801    ,       ///Q PHASE
    MenuButtonId_802    ,       ///RB GAIN CONTROL SETTING
    MenuButtonId_803    ,       ///R GAIN AWB PRE
    MenuButtonId_804    ,       ///B GAIN AWB PRE
    MenuButtonId_805    ,       ///R GAIN AWB A
    MenuButtonId_806    ,       ///B GAIN AWB A
    MenuButtonId_807    ,       ///R GAIN AWB B
    MenuButtonId_808    ,       ///B GAIN AWB B
    MenuButtonId_809    ,       ///AWB A GAIN OFFSET
    MenuButtonId_810    ,       ///ON
    MenuButtonId_811    ,       ///OFF
    MenuButtonId_812    ,       ///AWB B GAIN OFFSET
    MenuButtonId_813    ,       ///ON
    MenuButtonId_814    ,       ///OFF
    MenuButtonId_815    ,       ///COLOR TEMP Ach SETTING
    MenuButtonId_816    ,       ///COLOR TEMP
    MenuButtonId_817    ,       ///R Gain
    MenuButtonId_818    ,       ///B Gain
    MenuButtonId_819    ,       ///G AXIS
    MenuButtonId_820    ,       ///COLOR TEMP Bch SETTING
    MenuButtonId_821    ,       ///COLOR TEMP
    MenuButtonId_822    ,       ///R Gain
    MenuButtonId_823    ,       ///B Gain
    MenuButtonId_824    ,       ///G AXIS
    MenuButtonId_825    ,       ///CHROMA LEVEL
    MenuButtonId_826    ,       ///CHROMA PHASE
    MenuButtonId_827    ,       ///MATRIX
    MenuButtonId_828    ,       ///NORM1
    MenuButtonId_829    ,       ///NORM2
    MenuButtonId_830    ,       ///FLUO
    MenuButtonId_831    ,       ///CINELIKE
    MenuButtonId_832    ,       ///MATRIX SETTING
    MenuButtonId_833    ,       ///R-G
    MenuButtonId_834    ,       ///R-B
    MenuButtonId_835    ,       ///G-R
    MenuButtonId_836    ,       ///G-B
    MenuButtonId_837    ,       ///B-R
    MenuButtonId_838    ,       ///B-G
    MenuButtonId_839    ,       ///COLOR CORRECTION SETTING
    MenuButtonId_840    ,       ///R(SAT)
    MenuButtonId_841    ,       ///R(PHASE)
    MenuButtonId_842    ,       ///R-R-Mg(SAT)
    MenuButtonId_843    ,       ///R-R-Mg(PHASE)
    MenuButtonId_844    ,       ///R-Mg(SAT)
    MenuButtonId_845    ,       ///R-Mg(PHASE)
    MenuButtonId_846    ,       ///Mg(SAT)
    MenuButtonId_847    ,       ///Mg(PHASE)
    MenuButtonId_848    ,       ///Mg-B(SAT)
    MenuButtonId_849    ,       ///Mg-B(PHASE)
    MenuButtonId_850    ,       ///B(SAT)
    MenuButtonId_851    ,       ///B(PHASE)
    MenuButtonId_852    ,       ///B-Cy(SAT)
    MenuButtonId_853    ,       ///B-Cy(PHASE)
    MenuButtonId_854    ,       ///Cy(SAT)
    MenuButtonId_855    ,       ///Cy(PHASE)
    MenuButtonId_856    ,       ///Cy-G(SAT)
    MenuButtonId_857    ,       ///Cy-G(PHASE)
    MenuButtonId_858    ,       ///G(SAT)
    MenuButtonId_859    ,       ///G(PHASE)
    MenuButtonId_860    ,       ///G-Yl(SAT)
    MenuButtonId_861    ,       ///G-Yl(PHASE)
    MenuButtonId_862    ,       ///G-Yl-Yl(SAT)
    MenuButtonId_863    ,       ///G-Yl-Yl(PHASE)
    MenuButtonId_864    ,       ///Yl(SAT)
    MenuButtonId_865    ,       ///Yl(PHASE)
    MenuButtonId_866    ,       ///Yl-Yl-R(SAT)
    MenuButtonId_867    ,       ///Yl-Yl-R(PHASE)
    MenuButtonId_868    ,       ///Yl-R(SAT)
    MenuButtonId_869    ,       ///Yl-R(PHASE)
    MenuButtonId_870    ,       ///Yl-R-R(SAT)
    MenuButtonId_871    ,       ///Yl-R-R(PHASE)
    MenuButtonId_872    ,       ///MASTER PED
    MenuButtonId_873    ,       ///RGB BLACK CONTROL SETTING
    MenuButtonId_874    ,       ///R PED
    MenuButtonId_875    ,       ///G PED
    MenuButtonId_876    ,       ///B PED
    MenuButtonId_877    ,       ///PEDESTAL OFFSET
    MenuButtonId_878    ,       ///ON
    MenuButtonId_879    ,       ///OFF
    MenuButtonId_880    ,       ///GAMMA MODE SEL
    MenuButtonId_881    ,       ///HD
    MenuButtonId_882    ,       ///SD
    MenuButtonId_883    ,       ///FILMLIKE1
    MenuButtonId_884    ,       ///FILMLIKE2
    MenuButtonId_885    ,       ///FILMLIKE3
    MenuButtonId_886    ,       ///FILM-REC
    MenuButtonId_887    ,       ///VIDEO-REC
    MenuButtonId_888    ,       ///HLG
    MenuButtonId_889    ,       ///GAMMA SETTING
    MenuButtonId_890    ,       ///MASTER GAMMA
    MenuButtonId_891    ,       ///F-REC DYNAMIC LVL
    MenuButtonId_892    ,       ///200%
    MenuButtonId_893    ,       ///300%
    MenuButtonId_894    ,       ///400%
    MenuButtonId_895    ,       ///500%
    MenuButtonId_896    ,       ///600%
    MenuButtonId_897    ,       ///F-REC BLACK STR LVL
    MenuButtonId_898    ,       ///V-REC KNEE SLOPE
    MenuButtonId_899    ,       ///150%
    MenuButtonId_900    ,       ///200%
    MenuButtonId_901    ,       ///250%
    MenuButtonId_902    ,       ///300%
    MenuButtonId_903    ,       ///350%
    MenuButtonId_904    ,       ///400%
    MenuButtonId_905    ,       ///450%
    MenuButtonId_906    ,       ///500%
    MenuButtonId_907    ,       ///V-REC KNEE POINT
    MenuButtonId_908    ,       ///BLACK GAMMA
    MenuButtonId_909    ,       ///B. GAMMA RANGE
    MenuButtonId_910    ,       ///KNEE SETTING
    MenuButtonId_911    ,       ///KNEE MODE
    MenuButtonId_912    ,       ///AUTO
    MenuButtonId_913    ,       ///MANUAL
    MenuButtonId_914    ,       ///OFF
    MenuButtonId_915    ,       ///A.KNEE RESPONSE
    MenuButtonId_916    ,       ///KNEE POINT
    MenuButtonId_917    ,       ///KNEE SLOPE
    MenuButtonId_918    ,       ///HLG KNEE SW
    MenuButtonId_919    ,       ///ON
    MenuButtonId_920    ,       ///OFF
    MenuButtonId_921    ,       ///HLG KNEE POINT
    MenuButtonId_922    ,       ///HLG KNEE SLOPE
    MenuButtonId_923    ,       ///WHITE CLIP SETTING
    MenuButtonId_924    ,       ///WHITE CLIP
    MenuButtonId_925    ,       ///ON
    MenuButtonId_926    ,       ///OFF
    MenuButtonId_927    ,       ///WHITE CLIP LVL
    MenuButtonId_928    ,       ///DRS
    MenuButtonId_929    ,       ///ON
    MenuButtonId_930    ,       ///OFF
    MenuButtonId_931    ,       ///DRS EFFECT DEPTH
    MenuButtonId_932    ,       ///DNR
    MenuButtonId_933    ,       ///OFF
    MenuButtonId_934    ,       ///1
    MenuButtonId_935    ,       ///2
    MenuButtonId_936    ,       ///A.IRIS LEVEL
    MenuButtonId_937    ,       ///ON
    MenuButtonId_938    ,       ///OFF
    MenuButtonId_939    ,       ///A.IRIS LEVEL EFFECT
    MenuButtonId_940    ,       ///AUDIO
    MenuButtonId_941    ,       ///INPUT SETTINGS
    MenuButtonId_942    ,       ///INPUT1 MIC LEVEL
    MenuButtonId_943    ,       ///-40dB
    MenuButtonId_944    ,       ///-50dB
    MenuButtonId_945    ,       ///-60dB
    MenuButtonId_946    ,       ///INPUT2 MIC LEVEL
    MenuButtonId_947    ,       ///-40dB
    MenuButtonId_948    ,       ///-50dB
    MenuButtonId_949    ,       ///-60dB
    MenuButtonId_950    ,       ///INPUT1 LINE LEVEL
    MenuButtonId_951    ,       ///4dB
    MenuButtonId_952    ,       ///0dB
    MenuButtonId_953    ,       ///INPUT2 LINE LEVEL
    MenuButtonId_954    ,       ///4dB
    MenuButtonId_955    ,       ///0dB
    MenuButtonId_956    ,       ///REC CH SETTINGS
    MenuButtonId_957    ,       ///CH1 LEVEL
    MenuButtonId_958    ,       ///AUTO
    MenuButtonId_959    ,       ///MANUAL
    MenuButtonId_960    ,       ///CH2 LEVEL
    MenuButtonId_961    ,       ///AUTO
    MenuButtonId_962    ,       ///MANUAL
    MenuButtonId_963    ,       ///CH3 LEVEL
    MenuButtonId_964    ,       ///AUTO
    MenuButtonId_965    ,       ///MANUAL
    MenuButtonId_966    ,       ///CH4 LEVEL
    MenuButtonId_967    ,       ///AUTO
    MenuButtonId_968    ,       ///MANUAL
    MenuButtonId_969    ,       ///CH3 LEVEL CONTROL
    MenuButtonId_970    ,       ///CH4 LEVEL CONTROL
    MenuButtonId_971    ,       ///CH1 MIC LOWCUT
    MenuButtonId_972    ,       ///ON
    MenuButtonId_973    ,       ///OFF
    MenuButtonId_974    ,       ///CH2 MIC LOWCUT
    MenuButtonId_975    ,       ///ON
    MenuButtonId_976    ,       ///OFF
    MenuButtonId_977    ,       ///CH3 MIC LOWCUT
    MenuButtonId_978    ,       ///ON
    MenuButtonId_979    ,       ///OFF
    MenuButtonId_980    ,       ///CH4 MIC LOWCUT
    MenuButtonId_981    ,       ///ON
    MenuButtonId_982    ,       ///OFF
    MenuButtonId_983    ,       ///CH1 LIMITER
    MenuButtonId_984    ,       ///ON
    MenuButtonId_985    ,       ///OFF
    MenuButtonId_986    ,       ///CH2 LIMITER
    MenuButtonId_987    ,       ///ON
    MenuButtonId_988    ,       ///OFF
    MenuButtonId_989    ,       ///CH3 LIMITER
    MenuButtonId_990    ,       ///ON
    MenuButtonId_991    ,       ///OFF
    MenuButtonId_992    ,       ///CH4 LIMITER
    MenuButtonId_993    ,       ///ON
    MenuButtonId_994    ,       ///OFF
    MenuButtonId_995    ,       ///HEAD ROOM
    MenuButtonId_996    ,       ///12dB
    MenuButtonId_997    ,       ///18dB
    MenuButtonId_998    ,       ///20dB
    MenuButtonId_999    ,       ///OUTPUT SETTINGS
    MenuButtonId_1000   ,       ///AUDIO OUT
    MenuButtonId_1001   ,       ///CH1
    MenuButtonId_1002   ,       ///CH2
    MenuButtonId_1003   ,       ///CH1/2 STEREO 
    MenuButtonId_1004   ,       ///CH1/2 MIX
    MenuButtonId_1005   ,       ///CH3
    MenuButtonId_1006   ,       ///CH4
    MenuButtonId_1007   ,       ///CH3/4 STEREO
    MenuButtonId_1008   ,       ///CH3/4 MIX
    MenuButtonId_1009   ,       ///ALARM
    MenuButtonId_1010   ,       ///BATTERY END
    MenuButtonId_1011   ,       ///HIGH
    MenuButtonId_1012   ,       ///MED
    MenuButtonId_1013   ,       ///LOW
    MenuButtonId_1014   ,       ///OFF
    MenuButtonId_1015   ,       ///MEDIA END
    MenuButtonId_1016   ,       ///HIGH
    MenuButtonId_1017   ,       ///MED
    MenuButtonId_1018   ,       ///LOW
    MenuButtonId_1019   ,       ///OFF
    MenuButtonId_1020   ,       ///WARNING
    MenuButtonId_1021   ,       ///HIGH
    MenuButtonId_1022   ,       ///MED
    MenuButtonId_1023   ,       ///LOW
    MenuButtonId_1024   ,       ///OFF
    MenuButtonId_1025   ,       ///VIDEO OUT/LCD/VF
    MenuButtonId_1026   ,       ///VIDEO OUT SEL
    MenuButtonId_1027   ,       ///SDI + HDMI
    MenuButtonId_1028   ,       ///AV + HDMI
    MenuButtonId_1029   ,       ///SDI OUT
    MenuButtonId_1030   ,       ///OUTPUT SW
    MenuButtonId_1031   ,       ///ON
    MenuButtonId_1032   ,       ///OFF
    MenuButtonId_1033   ,       ///OUT FORMAT
    MenuButtonId_1034   ,       ///1920x1080p
    MenuButtonId_1035   ,       ///1920x1080i
    MenuButtonId_1036   ,       ///1920x1080PsF
    MenuButtonId_1037   ,       ///1280x720p
    MenuButtonId_1038   ,       ///720x480i
    MenuButtonId_1039   ,       ///720x576i
    MenuButtonId_1040   ,       ///3G-SDI OUT
    MenuButtonId_1041   ,       ///LEVEL-A
    MenuButtonId_1042   ,       ///LEVEL-B
    MenuButtonId_1043   ,       ///SD-SDI EDH
    MenuButtonId_1044   ,       ///ON
    MenuButtonId_1045   ,       ///OFF
    MenuButtonId_1046   ,       ///SDI REC REMOTE
    MenuButtonId_1047   ,       ///ON
    MenuButtonId_1048   ,       ///OFF
    MenuButtonId_1049   ,       ///SDI OUT CHAR
    MenuButtonId_1050   ,       ///ON
    MenuButtonId_1051   ,       ///OFF
    MenuButtonId_1052   ,       ///SDI OUT ZEBRA
    MenuButtonId_1053   ,       ///ON
    MenuButtonId_1054   ,       ///OFF
    MenuButtonId_1055   ,       ///SDI OUT HDR
    MenuButtonId_1056   ,       ///SDR
    MenuButtonId_1057   ,       ///HDR
    MenuButtonId_1058   ,       ///HDMI OUT
    MenuButtonId_1059   ,       ///OUT FORMAT
    MenuButtonId_1060   ,       ///3840x2160p
    MenuButtonId_1061   ,       ///3840x2160p(420/8bit),
    MenuButtonId_1062   ,       ///1920x1080p
    MenuButtonId_1063   ,       ///1920x1080i
    MenuButtonId_1064   ,       ///1280x720p
    MenuButtonId_1065   ,       ///720x480p
    MenuButtonId_1066   ,       ///720x576p
    MenuButtonId_1067   ,       ///HDMI TC OUT
    MenuButtonId_1068   ,       ///ON
    MenuButtonId_1069   ,       ///OFF
    MenuButtonId_1070   ,       ///HDMI REC REMOTE
    MenuButtonId_1071   ,       ///ON
    MenuButtonId_1072   ,       ///OFF
    MenuButtonId_1073   ,       ///HDMI OUT CHAR
    MenuButtonId_1074   ,       ///ON
    MenuButtonId_1075   ,       ///OFF
    MenuButtonId_1076   ,       ///HDMI OUT ZEBRA
    MenuButtonId_1077   ,       ///ON
    MenuButtonId_1078   ,       ///OFF
    MenuButtonId_1079   ,       ///HDMI OUT HDR
    MenuButtonId_1080   ,       ///SDR
    MenuButtonId_1081   ,       ///HDR
    MenuButtonId_1082   ,       ///AV OUT
    MenuButtonId_1083   ,       ///OUTPUT SW
    MenuButtonId_1084   ,       ///ON
    MenuButtonId_1085   ,       ///OFF
    MenuButtonId_1086   ,       ///AV OUT CHAR
    MenuButtonId_1087   ,       ///ON
    MenuButtonId_1088   ,       ///OFF
    MenuButtonId_1089   ,       ///AV OUT ZEBRA
    MenuButtonId_1090   ,       ///ON
    MenuButtonId_1091   ,       ///OFF
    MenuButtonId_1092   ,       ///SD DOWNCON MODE
    MenuButtonId_1093   ,       ///SIDE CROP
    MenuButtonId_1094   ,       ///LETTER BOX
    MenuButtonId_1095   ,       ///SQUEEZE
    MenuButtonId_1096   ,       ///LCD
    MenuButtonId_1097   ,       ///BRIGHTNESS
    MenuButtonId_1098   ,       ///COLOR LEVEL
    MenuButtonId_1099   ,       ///CONTRAST
    MenuButtonId_1100   ,       ///BACK LIGHT
    MenuButtonId_1101   ,       ///2
    MenuButtonId_1102   ,       ///1
    MenuButtonId_1103   ,       ///0
    MenuButtonId_1104   ,       ///-1
    MenuButtonId_1105   ,       ///SELF SHOOT
    MenuButtonId_1106   ,       ///NORMAL
    MenuButtonId_1107   ,       ///MIRROR
    MenuButtonId_1108   ,       ///VF
    MenuButtonId_1109   ,       ///BRIGHTNESS
    MenuButtonId_1110   ,       ///COLOR LEVEL
    MenuButtonId_1111   ,       ///CONTRAST
    MenuButtonId_1112   ,       ///VF COLOR
    MenuButtonId_1113   ,       ///ON
    MenuButtonId_1114   ,       ///OFF
    MenuButtonId_1115   ,       ///EYE SENSOR
    MenuButtonId_1116   ,       ///HIGH
    MenuButtonId_1117   ,       ///LOW
    MenuButtonId_1118   ,       ///LCD/VF HDR
    MenuButtonId_1119   ,       ///SDR
    MenuButtonId_1120   ,       ///HDR
    MenuButtonId_1121   ,       ///INDICATOR
    MenuButtonId_1122   ,       ///FULL AUTO
    MenuButtonId_1123   ,       ///ON
    MenuButtonId_1124   ,       ///OFF
    MenuButtonId_1125   ,       ///SLOT1/2 STATUS
    MenuButtonId_1126   ,       ///ON
    MenuButtonId_1127   ,       ///OFF
    MenuButtonId_1128   ,       ///2 SLOTS FUNC.
    MenuButtonId_1129   ,       ///ON
    MenuButtonId_1130   ,       ///OFF
    MenuButtonId_1131   ,       ///STREAMING
    MenuButtonId_1132   ,       ///ON
    MenuButtonId_1133   ,       ///OFF
    MenuButtonId_1134   ,       ///NETWORK
    MenuButtonId_1135   ,       ///ON
    MenuButtonId_1136   ,       ///OFF
    MenuButtonId_1137   ,       ///BATTERY REMAIN
    MenuButtonId_1138   ,       ///ON
    MenuButtonId_1139   ,       ///OFF
    MenuButtonId_1140   ,       ///REC FORMAT
    MenuButtonId_1141   ,       ///ON
    MenuButtonId_1142   ,       ///OFF
    MenuButtonId_1143   ,       ///FRAME RATE
    MenuButtonId_1144   ,       ///ON
    MenuButtonId_1145   ,       ///OFF
    MenuButtonId_1146   ,       ///BONDING DEVICE
    MenuButtonId_1147   ,       ///ON
    MenuButtonId_1148   ,       ///OFF
    MenuButtonId_1149   ,       ///REC REMOTE
    MenuButtonId_1150   ,       ///ON
    MenuButtonId_1151   ,       ///OFF
    MenuButtonId_1152   ,       ///REC MODE
    MenuButtonId_1153   ,       ///ON
    MenuButtonId_1154   ,       ///OFF
    MenuButtonId_1155   ,       ///FBC
    MenuButtonId_1156   ,       ///ON
    MenuButtonId_1157   ,       ///OFF
    MenuButtonId_1158   ,       ///HDR/DRS
    MenuButtonId_1159   ,       ///ON
    MenuButtonId_1160   ,       ///OFF
    MenuButtonId_1161   ,       ///OIS
    MenuButtonId_1162   ,       ///ON
    MenuButtonId_1163   ,       ///OFF
    MenuButtonId_1164   ,       ///SCENE FILE
    MenuButtonId_1165   ,       ///ON
    MenuButtonId_1166   ,       ///OFF
    MenuButtonId_1167   ,       ///AREA
    MenuButtonId_1168   ,       ///ON
    MenuButtonId_1169   ,       ///OFF
    MenuButtonId_1170   ,       ///AUDIO LEVEL METER
    MenuButtonId_1171   ,       ///ON
    MenuButtonId_1172   ,       ///OFF
    MenuButtonId_1173   ,       ///GAIN
    MenuButtonId_1174   ,       ///ON
    MenuButtonId_1175   ,       ///OFF
    MenuButtonId_1176   ,       ///ND FILTER
    MenuButtonId_1177   ,       ///ON
    MenuButtonId_1178   ,       ///OFF
    MenuButtonId_1179   ,       ///SHUTTER
    MenuButtonId_1180   ,       ///ON
    MenuButtonId_1181   ,       ///OFF
    MenuButtonId_1182   ,       ///IRIS
    MenuButtonId_1183   ,       ///ON
    MenuButtonId_1184   ,       ///OFF
    MenuButtonId_1185   ,       ///ZOOM/FOCUS
    MenuButtonId_1186   ,       ///NUMBER
    MenuButtonId_1187   ,       ///mm/feet
    MenuButtonId_1188   ,       ///mm/m
    MenuButtonId_1189   ,       ///OFF
    MenuButtonId_1190   ,       ///WHITE BALANCE
    MenuButtonId_1191   ,       ///ON
    MenuButtonId_1192   ,       ///OFF
    MenuButtonId_1193   ,       ///DATE/TIME
    MenuButtonId_1194   ,       ///OFF
    MenuButtonId_1195   ,       ///DATE
    MenuButtonId_1196   ,       ///TIME
    MenuButtonId_1197   ,       ///DATE&TIME
    MenuButtonId_1198   ,       ///SHOOTING MODE
    MenuButtonId_1199   ,       ///ON
    MenuButtonId_1200   ,       ///OFF
    MenuButtonId_1201   ,       ///MULTI MANUAL
    MenuButtonId_1202   ,       ///ON
    MenuButtonId_1203   ,       ///OFF
    MenuButtonId_1204   ,       ///D.ZOOM
    MenuButtonId_1205   ,       ///ON
    MenuButtonId_1206   ,       ///OFF
    MenuButtonId_1207   ,       ///IR REC
    MenuButtonId_1208   ,       ///ON
    MenuButtonId_1209   ,       ///OFF
    MenuButtonId_1210   ,       ///PLAYBACK STATUS
    MenuButtonId_1211   ,       ///ON
    MenuButtonId_1212   ,       ///OFF
    MenuButtonId_1213   ,       ///MARKER
    MenuButtonId_1214   ,       ///CENTER MARKER
    MenuButtonId_1215   ,       ///1
    MenuButtonId_1216   ,       ///2
    MenuButtonId_1217   ,       ///3
    MenuButtonId_1218   ,       ///4
    MenuButtonId_1219   ,       ///OFF
    MenuButtonId_1220   ,       ///SAFETY MARK
    MenuButtonId_1221   ,       ///1
    MenuButtonId_1222   ,       ///2
    MenuButtonId_1223   ,       ///OFF
    MenuButtonId_1224   ,       ///SAFETY AREA
    MenuButtonId_1225   ,       ///FRAME MARKER
    MenuButtonId_1226   ,       ///4:3
    MenuButtonId_1227   ,       ///13:9
    MenuButtonId_1228   ,       ///14:9
    MenuButtonId_1229   ,       ///1.85:1
    MenuButtonId_1230   ,       ///2.35:1
    MenuButtonId_1231   ,       ///OFF
    MenuButtonId_1232   ,       ///FRAME COLOR
    MenuButtonId_1233   ,       ///WHITE
    MenuButtonId_1234   ,       ///BLACK
    MenuButtonId_1235   ,       ///RED
    MenuButtonId_1236   ,       ///GREEN
    MenuButtonId_1237   ,       ///BLUE
    MenuButtonId_1238   ,       ///YELLOW
    MenuButtonId_1239   ,       ///FOCUS ASSIST
    MenuButtonId_1240   ,       ///FOCUS ASSIST SW
    MenuButtonId_1241   ,       ///EXPAND
    MenuButtonId_1242   ,       ///PEAKING
    MenuButtonId_1243   ,       ///EXPAND MODE
    MenuButtonId_1244   ,       ///10SEC
    MenuButtonId_1245   ,       ///HOLD
    MenuButtonId_1246   ,       ///UNTIL REC
    MenuButtonId_1247   ,       ///EXPAND VALUE
    MenuButtonId_1248   ,       ///x2
    MenuButtonId_1249   ,       ///x3
    MenuButtonId_1250   ,       ///x4
    MenuButtonId_1251   ,       ///PEAKING LEVEL
    MenuButtonId_1252   ,       ///LOW
    MenuButtonId_1253   ,       ///MID
    MenuButtonId_1254   ,       ///HIGH
    MenuButtonId_1255   ,       ///PEAKING COLOR
    MenuButtonId_1256   ,       ///RED
    MenuButtonId_1257   ,       ///GREEN
    MenuButtonId_1258   ,       ///WHITE
    MenuButtonId_1259   ,       ///BLACK & WHITE
    MenuButtonId_1260   ,       ///ON
    MenuButtonId_1261   ,       ///OFF
    MenuButtonId_1262   ,       ///DURING PEAKING
    MenuButtonId_1263   ,       ///DETAIL
    MenuButtonId_1264   ,       ///ON
    MenuButtonId_1265   ,       ///OFF
    MenuButtonId_1266   ,       ///DETAIL LEVEL
    MenuButtonId_1267   ,       ///DETAIL FREQ.
    MenuButtonId_1268   ,       ///HIGH
    MenuButtonId_1269   ,       ///LOW
    MenuButtonId_1270   ,       ///EI ASSIST
    MenuButtonId_1271   ,       ///ZEBRA
    MenuButtonId_1272   ,       ///MOMENT
    MenuButtonId_1273   ,       ///ON
    MenuButtonId_1274   ,       ///OFF
    MenuButtonId_1275   ,       ///ZEBRA1 DETECT
    MenuButtonId_1276   ,       ///ZEBRA2 DETECT
    MenuButtonId_1277   ,       ///ZEBRA2
    MenuButtonId_1278   ,       ///ON
    MenuButtonId_1279   ,       ///SPOT
    MenuButtonId_1280   ,       ///OFF
    MenuButtonId_1281   ,       ///WFM MODE
    MenuButtonId_1282   ,       ///WAVE
    MenuButtonId_1283   ,       ///VECTOR
    MenuButtonId_1284   ,       ///WAVE/VECTOR
    MenuButtonId_1285   ,       ///WFM TRANSPARENCE
    MenuButtonId_1286   ,       ///0%
    MenuButtonId_1287   ,       ///25%
    MenuButtonId_1288   ,       ///50%
    MenuButtonId_1289   ,       ///LCD/VF LEVEL GAUGE
    MenuButtonId_1290   ,       ///LEVEL GAUGE
    MenuButtonId_1291   ,       ///ON
    MenuButtonId_1292   ,       ///OFF
    MenuButtonId_1293   ,       ///LEVEL GAUGE RESET
    MenuButtonId_1294   ,       ///YES
    MenuButtonId_1295   ,       ///NO
    MenuButtonId_1296   ,       ///RECORDING
    MenuButtonId_1297   ,       ///FORMAT MEDIA
    MenuButtonId_1298   ,       ///SLOT1
    MenuButtonId_1299   ,       ///SLOT2
    MenuButtonId_1300   ,       ///CLIP NAME
    MenuButtonId_1301   ,       ///CAM INDEX
    MenuButtonId_1302   ,       ///NEXT CARD COUNT
    MenuButtonId_1303   ,       ///FILE SPLIT
    MenuButtonId_1304   ,       ///ONE FILE
    MenuButtonId_1305   ,       ///SPLIT
    MenuButtonId_1306   ,       ///SHORT SPLIT
    MenuButtonId_1307   ,       ///2 SLOTS FUNC.
    MenuButtonId_1308   ,       ///OFF
    MenuButtonId_1309   ,       ///RELAY REC
    MenuButtonId_1310   ,       ///SIMUL REC
    MenuButtonId_1311   ,       ///BACKGR REC
    MenuButtonId_1312   ,       ///PRE REC
    MenuButtonId_1313   ,       ///ON
    MenuButtonId_1314   ,       ///OFF
    MenuButtonId_1315   ,       ///REC FUNCTION
    MenuButtonId_1316   ,       ///REC MODE
    MenuButtonId_1317   ,       ///NORMAL
    MenuButtonId_1318   ,       ///INTERVAL
    MenuButtonId_1319   ,       ///ONE SHOT
    MenuButtonId_1320   ,       ///LOOP
    MenuButtonId_1321   ,       ///REC MODE HOLD
    MenuButtonId_1322   ,       ///ON
    MenuButtonId_1323   ,       ///OFF
    MenuButtonId_1324   ,       ///INTERVAL TIME
    MenuButtonId_1325   ,       ///1s
    MenuButtonId_1326   ,       ///2s
    MenuButtonId_1327   ,       ///5s
    MenuButtonId_1328   ,       ///10s
    MenuButtonId_1329   ,       ///30s
    MenuButtonId_1330   ,       ///1min
    MenuButtonId_1331   ,       ///5min
    MenuButtonId_1332   ,       ///10min
    MenuButtonId_1333   ,       ///ONE SHOT TIME
    MenuButtonId_1334   ,       ///1frm
    MenuButtonId_1335   ,       ///2frm
    MenuButtonId_1336   ,       ///4frm
    MenuButtonId_1337   ,       ///8frm
    MenuButtonId_1338   ,       ///16frm
    MenuButtonId_1339   ,       ///1s
    MenuButtonId_1340   ,       ///START DELAY
    MenuButtonId_1341   ,       ///ON
    MenuButtonId_1342   ,       ///OFF
    MenuButtonId_1343   ,       ///TC/UB
    MenuButtonId_1344   ,       ///TC PRESET
    MenuButtonId_1345   ,       ///UB PRESET
    MenuButtonId_1346   ,       ///FREE/REC RUN
    MenuButtonId_1347   ,       ///FREE RUN
    MenuButtonId_1348   ,       ///REC RUN
    MenuButtonId_1349   ,       ///DF/NDF
    MenuButtonId_1350   ,       ///DF
    MenuButtonId_1351   ,       ///NDF
    MenuButtonId_1352   ,       ///UB MODE
    MenuButtonId_1353   ,       ///FRAME RATE
    MenuButtonId_1354   ,       ///USER
    MenuButtonId_1355   ,       ///TIME
    MenuButtonId_1356   ,       ///DATE
    MenuButtonId_1357   ,       ///TC
    MenuButtonId_1358   ,       ///CLIP NAME
    MenuButtonId_1359   ,       ///TC IN/OUT SEL
    MenuButtonId_1360   ,       ///TC IN
    MenuButtonId_1361   ,       ///TC OUT
    MenuButtonId_1362   ,       ///TC OUT REF
    MenuButtonId_1363   ,       ///RECORDING
    MenuButtonId_1364   ,       ///SDI OUT
    MenuButtonId_1365   ,       ///REC COUNTER
    MenuButtonId_1366   ,       ///TOTAL
    MenuButtonId_1367   ,       ///CLIP
    MenuButtonId_1368   ,       ///TIME STAMP
    MenuButtonId_1369   ,       ///OFF
    MenuButtonId_1370   ,       ///DATE
    MenuButtonId_1371   ,       ///TIME
    MenuButtonId_1372   ,       ///DATE&TIME
    MenuButtonId_1373   ,       ///REC META DATA
    MenuButtonId_1374   ,       ///LOAD
    MenuButtonId_1375   ,       ///RECORD
    MenuButtonId_1376   ,       ///ON
    MenuButtonId_1377   ,       ///OFF
    MenuButtonId_1378   ,       ///USER CLIP NAME
    MenuButtonId_1379   ,       ///TYPE1
    MenuButtonId_1380   ,       ///TYPE2
    MenuButtonId_1381   ,       ///START TEXT MEMO
    MenuButtonId_1382   ,       ///ON
    MenuButtonId_1383   ,       ///OFF
    MenuButtonId_1384   ,       ///CARD SERIAL
    MenuButtonId_1385   ,       ///ON
    MenuButtonId_1386   ,       ///OFF
    MenuButtonId_1387   ,       ///INITIALIZE
    MenuButtonId_1388   ,       ///YES
    MenuButtonId_1389   ,       ///NO
    MenuButtonId_1390   ,       ///PROPERTIES
    MenuButtonId_1391   ,       ///NETWORK
    MenuButtonId_1392   ,       ///DEVICE SEL
    MenuButtonId_1393   ,       ///LAN
    MenuButtonId_1394   ,       ///WLAN
    MenuButtonId_1395   ,       ///CELLULAR
    MenuButtonId_1396   ,       ///OFF
    MenuButtonId_1397   ,       ///NETWORK FUNC
    MenuButtonId_1398   ,       ///FTP CLIENT
    MenuButtonId_1399   ,       ///STREAMING
    MenuButtonId_1400   ,       ///NDI|HX
    MenuButtonId_1401   ,       ///OFF
    MenuButtonId_1402   ,       ///IP REMOTE
    MenuButtonId_1403   ,       ///ENABLE/DISABLE
    MenuButtonId_1404   ,       ///ENABLE
    MenuButtonId_1405   ,       ///DISABLE
    MenuButtonId_1406   ,       ///USER ACCOUNT
    MenuButtonId_1407   ,       ///ACCOUNT LIST
    MenuButtonId_1408   ,       ///PORT
    MenuButtonId_1409   ,       ///FTP CLIENT
    MenuButtonId_1410   ,       ///CONNECTION INFO.
    MenuButtonId_1411   ,       ///MEMORY
    MenuButtonId_1412   ,       ///SD CARD
    MenuButtonId_1413   ,       ///DATA TYPE
    MenuButtonId_1414   ,       ///GENERAL
    MenuButtonId_1415   ,       ///P2CAST
    MenuButtonId_1416   ,       ///SERVER URL
    MenuButtonId_1417   ,       ///LOGIN USER
    MenuButtonId_1418   ,       ///LOGIN PASSWORD
    MenuButtonId_1419   ,       ///LOAD (SD CARD)
    MenuButtonId_1420   ,       ///YES
    MenuButtonId_1421   ,       ///NO
    MenuButtonId_1422   ,       ///SAVE (SD CARD)
    MenuButtonId_1423   ,       ///YES
    MenuButtonId_1424   ,       ///NO
    MenuButtonId_1425   ,       ///CLEAR (MEMORY)
    MenuButtonId_1426   ,       ///YES
    MenuButtonId_1427   ,       ///NO
    MenuButtonId_1428   ,       ///REC DURING UPLOAD
    MenuButtonId_1429   ,       ///ENABLE
    MenuButtonId_1430   ,       ///DISABLE
    MenuButtonId_1431   ,       ///AUTO UPLOAD
    MenuButtonId_1432   ,       ///REC CLIP(PROXY) 
    MenuButtonId_1433   ,       ///REC CLIP
    MenuButtonId_1434   ,       ///DISABLE
    MenuButtonId_1435   ,       ///UPLOAD LIST
    MenuButtonId_1436   ,       ///STREAMING
    MenuButtonId_1437   ,       ///STREAMING FORMAT
    MenuButtonId_1438   ,       ///1920x1080-60fps 24M
    MenuButtonId_1439   ,       ///1920x1080-60fps 20M
    MenuButtonId_1440   ,       ///1920x1080-60fps 16M
    MenuButtonId_1441   ,       ///1920x1080-50fps 24M
    MenuButtonId_1442   ,       ///1920x1080-50fps 20M
    MenuButtonId_1443   ,       ///1920x1080-50fps 16M
    MenuButtonId_1444   ,       ///1920x1080-30fps 14M
    MenuButtonId_1445   ,       ///1920x1080-30fps 6M
    MenuButtonId_1446   ,       ///1920x1080-30fps 1M
    MenuButtonId_1447   ,       ///1920x1080-25fps 14M
    MenuButtonId_1448   ,       ///1920x1080-25fps 6M
    MenuButtonId_1449   ,       ///1920x1080-25fps 1M
    MenuButtonId_1450   ,       ///1920x1080-24fps 14M
    MenuButtonId_1451   ,       ///1920x1080-24fps 6M
    MenuButtonId_1452   ,       ///1920x1080-24fps 1M
    MenuButtonId_1453   ,       ///1280x720-60fps 14M
    MenuButtonId_1454   ,       ///1280x720-60fps 8M
    MenuButtonId_1455   ,       ///1280x720-60fps 3M
    MenuButtonId_1456   ,       ///1280x720-50fps 14M
    MenuButtonId_1457   ,       ///1280x720-50fps 8M
    MenuButtonId_1458   ,       ///1280x720-50fps 3M
    MenuButtonId_1459   ,       ///1280x720-30fps 8M
    MenuButtonId_1460   ,       ///1280x720-30fps 2M
    MenuButtonId_1461   ,       ///1280x720-30fps 1M
    MenuButtonId_1462   ,       ///1280x720-25fps 8M
    MenuButtonId_1463   ,       ///1280x720-25fps 2M
    MenuButtonId_1464   ,       ///1280x720-25fps 1M
    MenuButtonId_1465   ,       ///1280x720-24fps 8M
    MenuButtonId_1466   ,       ///1280x720-24fps 2M
    MenuButtonId_1467   ,       ///1280x720-24fps 1M
    MenuButtonId_1468   ,       ///640x360-30fps 4M
    MenuButtonId_1469   ,       ///640x360-30fps 1.5M
    MenuButtonId_1470   ,       ///640x360-30fps 0.7M
    MenuButtonId_1471   ,       ///640x360-25fps 4M
    MenuButtonId_1472   ,       ///640x360-25fps 1.5M
    MenuButtonId_1473   ,       ///640x360-25fps 0.7M
    MenuButtonId_1474   ,       ///640x360-24fps 4M
    MenuButtonId_1475   ,       ///640x360-24fps 1.5M
    MenuButtonId_1476   ,       ///640x360-24fps 0.7M
    MenuButtonId_1477   ,       ///320x180-30fps 4M
    MenuButtonId_1478   ,       ///320x180-30fps 1.5M
    MenuButtonId_1479   ,       ///320x180-30fps 0.5M
    MenuButtonId_1480   ,       ///320x180-25fps 4M
    MenuButtonId_1481   ,       ///320x180-25fps 1.5M
    MenuButtonId_1482   ,       ///320x180-25fps 0.5M
    MenuButtonId_1483   ,       ///320x180-24fps 4M
    MenuButtonId_1484   ,       ///320x180-24fps 1.5M
    MenuButtonId_1485   ,       ///320x180-24fps 0.5M
    MenuButtonId_1486   ,       ///QoS MAX RATE
    MenuButtonId_1487   ,       ///QoS MIN RATE
    MenuButtonId_1488   ,       ///STREAMING LATENCY
    MenuButtonId_1489   ,       ///START TRIGGER
    MenuButtonId_1490   ,       ///CAMERA
    MenuButtonId_1491   ,       ///RECIEVER
    MenuButtonId_1492   ,       ///CONNECTION INFO.
    MenuButtonId_1493   ,       ///MEMORY
    MenuButtonId_1494   ,       ///SD CARD
    MenuButtonId_1495   ,       ///DATA TYPE
    MenuButtonId_1496   ,       ///GENERAL
    MenuButtonId_1497   ,       ///P2CAST
    MenuButtonId_1498   ,       ///LIVEU
    MenuButtonId_1499   ,       ///TVU
    MenuButtonId_1500   ,       ///RECEIVER URL
    MenuButtonId_1501   ,       ///LOAD (SD CARD)
    MenuButtonId_1502   ,       ///YES
    MenuButtonId_1503   ,       ///NO
    MenuButtonId_1504   ,       ///SAVE (SD CARD)
    MenuButtonId_1505   ,       ///YES
    MenuButtonId_1506   ,       ///NO
    MenuButtonId_1507   ,       ///CLEAR (MEMORY)
    MenuButtonId_1508   ,       ///YES
    MenuButtonId_1509   ,       ///NO
    MenuButtonId_1510   ,       ///START
    MenuButtonId_1511   ,       ///ON
    MenuButtonId_1512   ,       ///OFF
    MenuButtonId_1513   ,       ///NDI|HX
    MenuButtonId_1514   ,       ///ACTIVATION
    MenuButtonId_1515   ,       ///--
    MenuButtonId_1516   ,       ///NDI|HX
    MenuButtonId_1517   ,       ///STREAMING FORMAT
    MenuButtonId_1518   ,       ///1920x1080-60fps 24M
    MenuButtonId_1519   ,       ///1920x1080-60fps 16M
    MenuButtonId_1520   ,       ///1920x1080-60fps 10M
    MenuButtonId_1521   ,       ///1920x1080-60fps 8M
    MenuButtonId_1522   ,       ///1920x1080-50fps 24M
    MenuButtonId_1523   ,       ///1920x1080-50fps 16M
    MenuButtonId_1524   ,       ///1920x1080-50fps 10M
    MenuButtonId_1525   ,       ///1920x1080-50fps 8M
    MenuButtonId_1526   ,       ///1920x1080-30fps 14M
    MenuButtonId_1527   ,       ///1920x1080-30fps 10M
    MenuButtonId_1528   ,       ///1920x1080-30fps 6M
    MenuButtonId_1529   ,       ///1920x1080-25fps 14M
    MenuButtonId_1530   ,       ///1920x1080-25fps 10M
    MenuButtonId_1531   ,       ///1920x1080-25fps 6M
    MenuButtonId_1532   ,       ///1280x720-60fps 14M
    MenuButtonId_1533   ,       ///1280x720-60fps 10M
    MenuButtonId_1534   ,       ///1280x720-60fps 6M
    MenuButtonId_1535   ,       ///1280x720-50fps 14M
    MenuButtonId_1536   ,       ///1280x720-50fps 10M
    MenuButtonId_1537   ,       ///1280x720-50fps 6M
    MenuButtonId_1538   ,       ///1280x720-30fps 8M
    MenuButtonId_1539   ,       ///1280x720-30fps 4M
    MenuButtonId_1540   ,       ///1280x720-30fps 2M
    MenuButtonId_1541   ,       ///1280x720-25fps 8M
    MenuButtonId_1542   ,       ///1280x720-25fps 4M
    MenuButtonId_1543   ,       ///1280x720-25fps 2M
    MenuButtonId_1544   ,       ///CLEAR ACTIVATION
    MenuButtonId_1545   ,       ///YES
    MenuButtonId_1546   ,       ///NO
    MenuButtonId_1547   ,       ///LAN PROPERTY
    MenuButtonId_1548   ,       ///MAC ADDRESS
    MenuButtonId_1549   ,       ///IPv4 SETTING
    MenuButtonId_1550   ,       ///DHCP
    MenuButtonId_1551   ,       ///OFF
    MenuButtonId_1552   ,       ///CLIENT
    MenuButtonId_1553   ,       ///SERVER
    MenuButtonId_1554   ,       ///IP ADDRESS
    MenuButtonId_1555   ,       ///SUBNET MASK
    MenuButtonId_1556   ,       ///DEFAULT GATEWAY
    MenuButtonId_1557   ,       ///PRIMARY DNS
    MenuButtonId_1558   ,       ///SECONDARY DNS
    MenuButtonId_1559   ,       ///IPv6 SETTING
    MenuButtonId_1560   ,       ///ENABLE/DISABLE
    MenuButtonId_1561   ,       ///ENABLE
    MenuButtonId_1562   ,       ///DISABLE
    MenuButtonId_1563   ,       ///DHCP
    MenuButtonId_1564   ,       ///OFF
    MenuButtonId_1565   ,       ///CLIENT
    MenuButtonId_1566   ,       ///SERVER
    MenuButtonId_1567   ,       ///IP ADDRESS
    MenuButtonId_1568   ,       ///PREFIX LENGTH
    MenuButtonId_1569   ,       ///DEFAULT GATEWAY
    MenuButtonId_1570   ,       ///PRIMARY DNS
    MenuButtonId_1571   ,       ///SECONDARY DNS
    MenuButtonId_1572   ,       ///WLAN PROPERTY
    MenuButtonId_1573   ,       ///MAC ADDRESS
    MenuButtonId_1574   ,       ///TYPE
    MenuButtonId_1575   ,       ///DIRECT
    MenuButtonId_1576   ,       ///INFRA(SELECT)
    MenuButtonId_1577   ,       ///INFRA(MANUAL)
    MenuButtonId_1578   ,       ///SSID
    MenuButtonId_1579   ,       ///BAND
    MenuButtonId_1580   ,       ///2.4GHz
    MenuButtonId_1581   ,       ///5GHz
    MenuButtonId_1582   ,       ///CHANNEL(2.4GHz)
    MenuButtonId_1583   ,       ///AUTO
    MenuButtonId_1584   ,       ///CH1
    MenuButtonId_1585   ,       ///CH6
    MenuButtonId_1586   ,       ///CH11
    MenuButtonId_1587   ,       ///CHANNEL(5GHz)
    MenuButtonId_1588   ,       ///AUTO
    MenuButtonId_1589   ,       ///CH36
    MenuButtonId_1590   ,       ///CH40
    MenuButtonId_1591   ,       ///CH44
    MenuButtonId_1592   ,       ///CH48
    MenuButtonId_1593   ,       ///CH100
    MenuButtonId_1594   ,       ///CH104
    MenuButtonId_1595   ,       ///CH108
    MenuButtonId_1596   ,       ///CH112
    MenuButtonId_1597   ,       ///CH116
    MenuButtonId_1598   ,       ///CH132
    MenuButtonId_1599   ,       ///CH136
    MenuButtonId_1600   ,       ///CH140
    MenuButtonId_1601   ,       ///CH149
    MenuButtonId_1602   ,       ///CH153
    MenuButtonId_1603   ,       ///CH157
    MenuButtonId_1604   ,       ///CH161
    MenuButtonId_1605   ,       ///CH165
    MenuButtonId_1606   ,       ///ENCRYPTION
    MenuButtonId_1607   ,       ///WPA-TKIP
    MenuButtonId_1608   ,       ///WPA-AES
    MenuButtonId_1609   ,       ///WPA2-TKIP
    MenuButtonId_1610   ,       ///WPA2-AES
    MenuButtonId_1611   ,       ///NONE
    MenuButtonId_1612   ,       ///ENCRYPT KEY
    MenuButtonId_1613   ,       ///IPv4 SETTING
    MenuButtonId_1614   ,       ///DHCP
    MenuButtonId_1615   ,       ///OFF
    MenuButtonId_1616   ,       ///CLIENT
    MenuButtonId_1617   ,       ///SERVER
    MenuButtonId_1618   ,       ///IP ADDRESS
    MenuButtonId_1619   ,       ///SUBNET MASK
    MenuButtonId_1620   ,       ///DEFAULT GATEWAY
    MenuButtonId_1621   ,       ///PRIMARY DNS
    MenuButtonId_1622   ,       ///SECONDARY DNS
    MenuButtonId_1623   ,       ///IPv6 SETTING
    MenuButtonId_1624   ,       ///ENABLE/DISABLE
    MenuButtonId_1625   ,       ///ENABLE
    MenuButtonId_1626   ,       ///DISABLE
    MenuButtonId_1627   ,       ///DHCP
    MenuButtonId_1628   ,       ///OFF
    MenuButtonId_1629   ,       ///CLIENT
    MenuButtonId_1630   ,       ///SERVER
    MenuButtonId_1631   ,       ///IP ADDRESS
    MenuButtonId_1632   ,       ///PREFIXÅ@LENGTH
    MenuButtonId_1633   ,       ///DEFAULT GATEWAY
    MenuButtonId_1634   ,       ///PRIMARY DNS
    MenuButtonId_1635   ,       ///SECONDARY DNS
    MenuButtonId_1636   ,       ///CELLULAR PROPERTY
    MenuButtonId_1637   ,       ///APN
    MenuButtonId_1638   ,       ///USER ID
    MenuButtonId_1639   ,       ///PASSWORD
    MenuButtonId_1640   ,       ///DIAL NO.
    MenuButtonId_1641   ,       ///INFORMATION
    MenuButtonId_1642   ,       ///NETWORK ID
    MenuButtonId_1643   ,       ///STATUS
    MenuButtonId_1644   ,       ///LOG
    MenuButtonId_1645   ,       ///SAVE LOG (SDCARD)
    MenuButtonId_1646   ,       ///UTILITY
    MenuButtonId_1647   ,       ///NETWORK INITIALIZE
    MenuButtonId_1648   ,       ///EASY IP SETTING
    MenuButtonId_1649   ,       ///DISABLE
    MenuButtonId_1650   ,       ///20 MIN.
    MenuButtonId_1651   ,       ///UNLIMITED
    MenuButtonId_1652   ,       ///EASY IP CAMERA TITLE
    MenuButtonId_1653   ,       ///SYSTEM
    MenuButtonId_1654   ,       ///FREQUENCY
    MenuButtonId_1655   ,       ///59.94Hz
    MenuButtonId_1656   ,       ///50.00Hz
    MenuButtonId_1657   ,       ///FILE FORMAT
    MenuButtonId_1658   ,       ///P2
    MenuButtonId_1659   ,       ///MOV
    MenuButtonId_1660   ,       ///AVCHD
    MenuButtonId_1661   ,       ///FILE FORMAT
    MenuButtonId_1662   ,       ///P2
    MenuButtonId_1663   ,       ///MOV
    MenuButtonId_1664   ,       ///AVCHD
    MenuButtonId_1665   ,       ///REC FORMAT
    MenuButtonId_1666   ,       ///1080-59.94p/AVC-I100
    MenuButtonId_1667   ,       ///1080-59.94p/AVC-I422
    MenuButtonId_1668   ,       ///1080-59.94p/AVC-G25
    MenuButtonId_1669   ,       ///1080-59.94i/AVC-I200
    MenuButtonId_1670   ,       ///1080-59.94i/AVC-I100
    MenuButtonId_1671   ,       ///1080-59.94i/AVC-I50
    MenuButtonId_1672   ,       ///1080-59.94i/AVC-G50
    MenuButtonId_1673   ,       ///1080-59.94i/AVC-G25
    MenuButtonId_1674   ,       ///720-59.94p/AVC-I200
    MenuButtonId_1675   ,       ///720-59.94p/AVC-I100
    MenuButtonId_1676   ,       ///720-59.94p/AVC-I50
    MenuButtonId_1677   ,       ///720-59.94p/AVC-G50
    MenuButtonId_1678   ,       ///720-59.94p/AVC-G25
    MenuButtonId_1679   ,       ///REC FORMAT
    MenuButtonId_1680   ,       ///1080-50.00p/AVC-I100
    MenuButtonId_1681   ,       ///1080-50.00p/AVC-I422
    MenuButtonId_1682   ,       ///1080-50.00p/AVC-G25
    MenuButtonId_1683   ,       ///1080-50.00i/AVC-I200
    MenuButtonId_1684   ,       ///1080-50.00i/AVC-I100
    MenuButtonId_1685   ,       ///1080-50.00i/AVC-I50
    MenuButtonId_1686   ,       ///1080-50.00i/AVC-G50
    MenuButtonId_1687   ,       ///1080-50.00i/AVC-G25
    MenuButtonId_1688   ,       ///720-50.00p/AVC-I200
    MenuButtonId_1689   ,       ///720-50.00p/AVC-I100
    MenuButtonId_1690   ,       ///720-50.00p/AVC-I50
    MenuButtonId_1691   ,       ///720-50.00p/AVC-G50
    MenuButtonId_1692   ,       ///720-50.00p/AVC-G25
    MenuButtonId_1693   ,       ///REC FORMAT
    MenuButtonId_1694   ,       ///2160-59.94p/420LongGOP 150M
    MenuButtonId_1695   ,       ///2160-59.94p/HEVC 200M
    MenuButtonId_1696   ,       ///2160-29.97p/420LongGOP 100M
    MenuButtonId_1697   ,       ///2160-29.97p/HEVC 150M
    MenuButtonId_1698   ,       ///2160-29.97p/422LongGOP 150M
    MenuButtonId_1699   ,       ///2160-29.97p/422ALL-I 400M
    MenuButtonId_1700   ,       ///2160-23.98p/420LongGOP 100M
    MenuButtonId_1701   ,       ///2160-23.98p/HEVC 150M
    MenuButtonId_1702   ,       ///2160-23.98p/422LongGOP 150M
    MenuButtonId_1703   ,       ///2160-23.98p/422ALL-I 400M
    MenuButtonId_1704   ,       ///1080-59.94p/422LongGOP 100M
    MenuButtonId_1705   ,       ///1080-59.94p/422ALL-I 200M
    MenuButtonId_1706   ,       ///1080-59.94i/422LongGOP 50M
    MenuButtonId_1707   ,       ///1080-59.94i/422ALL-I 100M
    MenuButtonId_1708   ,       ///1080-29.97p/422LongGOP 50M
    MenuButtonId_1709   ,       ///1080-29.97p/422ALL-I 100M
    MenuButtonId_1710   ,       ///1080-23.98p/422LongGOP 50M
    MenuButtonId_1711   ,       ///1080-23.98p/422ALL-I 100M
    MenuButtonId_1712   ,       ///REC FORMAT
    MenuButtonId_1713   ,       ///2160-50.00p/420LongGOP 150M
    MenuButtonId_1714   ,       ///2160-50.00p/HEVC 200M
    MenuButtonId_1715   ,       ///2160-25.00p/420LongGOP 100M
    MenuButtonId_1716   ,       ///2160-25.00p/HEVC 150M
    MenuButtonId_1717   ,       ///2160-25.00p/422LongGOP 150M
    MenuButtonId_1718   ,       ///2160-25.00p/422ALL-I 400M
    MenuButtonId_1719   ,       ///1080-50.00p/422LongGOP 100M
    MenuButtonId_1720   ,       ///1080-50.00p/422ALL-I 200M
    MenuButtonId_1721   ,       ///1080-50.00i/422LongGOP 50M
    MenuButtonId_1722   ,       ///1080-50.00i/422ALL-I 100M
    MenuButtonId_1723   ,       ///1080-25.00p/422LongGOP 50M
    MenuButtonId_1724   ,       ///1080-25.00p/422ALL-I 100M
    MenuButtonId_1725   ,       ///REC FORMAT
    MenuButtonId_1726   ,       ///1080-59.94p/AVCHD PS
    MenuButtonId_1727   ,       ///1080-59.94i/AVCHD PH
    MenuButtonId_1728   ,       ///1080-59.94i/AVCHD HA
    MenuButtonId_1729   ,       ///1080-23.98p/AVCHD PH
    MenuButtonId_1730   ,       ///720-59.94p/AVCHD PM
    MenuButtonId_1731   ,       ///480-59.94i/AVCHD SA
    MenuButtonId_1732   ,       ///REC FORMAT
    MenuButtonId_1733   ,       ///1080-50.00p/AVCHD PS
    MenuButtonId_1734   ,       ///1080-50.00i/AVCHD PH
    MenuButtonId_1735   ,       ///1080-50.00i/AVCHD HA
    MenuButtonId_1736   ,       ///720-50.00p/AVCHD PM
    MenuButtonId_1737   ,       ///576-50.00i/AVCHD SA
    MenuButtonId_1738   ,       ///PROXY REC MODE
    MenuButtonId_1739   ,       ///MAIN
    MenuButtonId_1740   ,       ///MAIN & SUB
    MenuButtonId_1741   ,       ///OFF
    MenuButtonId_1742   ,       ///PROXY REC FORMAT
    MenuButtonId_1743   ,       ///LOW 2CH MOV
    MenuButtonId_1744   ,       ///HQ 2CH MOV
    MenuButtonId_1745   ,       ///SHQ 2CH MOV
    MenuButtonId_1746   ,       ///AVC-G6 2CH MOV
    MenuButtonId_1747   ,       ///ASPECT
    MenuButtonId_1748   ,       ///16:9
    MenuButtonId_1749   ,       ///4:3
    MenuButtonId_1750   ,       ///SUPER SLOW
    MenuButtonId_1751   ,       ///ON
    MenuButtonId_1752   ,       ///OFF
    MenuButtonId_1753   ,       ///SHOOTING MODE
    MenuButtonId_1754   ,       ///NORMAL
    MenuButtonId_1755   ,       ///HIGH SENS.
    MenuButtonId_1756   ,       ///OTHERS
    MenuButtonId_1757   ,       ///FILE
    MenuButtonId_1758   ,       ///LOAD/SAVE SLOT
    MenuButtonId_1759   ,       ///SLOT1
    MenuButtonId_1760   ,       ///SLOT2
    MenuButtonId_1761   ,       ///SCENE FILE(SD CARD)
    MenuButtonId_1762   ,       ///LOAD
    MenuButtonId_1763   ,       ///SAVE
    MenuButtonId_1764   ,       ///SAVE AS
    MenuButtonId_1765   ,       ///SETUP FILE(SD CARD)
    MenuButtonId_1766   ,       ///LOAD
    MenuButtonId_1767   ,       ///SAVE
    MenuButtonId_1768   ,       ///SAVE AS
    MenuButtonId_1769   ,       ///SETUP FILE(MEMORY)
    MenuButtonId_1770   ,       ///LOAD
    MenuButtonId_1771   ,       ///SAVE
    MenuButtonId_1772   ,       ///INITIALIZE
    MenuButtonId_1773   ,       ///COLOR BARS
    MenuButtonId_1774   ,       ///COLOR BARS TYPE
    MenuButtonId_1775   ,       ///SMPTE
    MenuButtonId_1776   ,       ///FULL
    MenuButtonId_1777   ,       ///TEST TONE
    MenuButtonId_1778   ,       ///ON
    MenuButtonId_1779   ,       ///OFF
    MenuButtonId_1780   ,       ///LED
    MenuButtonId_1781   ,       ///TALLY LED
    MenuButtonId_1782   ,       ///FRONT
    MenuButtonId_1783   ,       ///REAR
    MenuButtonId_1784   ,       ///BOTH
    MenuButtonId_1785   ,       ///OFF
    MenuButtonId_1786   ,       ///ACCESS LED
    MenuButtonId_1787   ,       ///ON
    MenuButtonId_1788   ,       ///OFF
    MenuButtonId_1789   ,       ///CLOCK
    MenuButtonId_1790   ,       ///CLOCK SETTING
    MenuButtonId_1791   ,       ///TIME ZONE
    MenuButtonId_1792   ,       ///DATE FORMAT
    MenuButtonId_1793   ,       ///Y-M-D
    MenuButtonId_1794   ,       ///M-D-Y
    MenuButtonId_1795   ,       ///D-M-Y
    MenuButtonId_1796   ,       ///USB DEVICE
    MenuButtonId_1797   ,       ///CARD READER MODE
    MenuButtonId_1798   ,       ///YES
    MenuButtonId_1799   ,       ///NO
    MenuButtonId_1800   ,       ///SERVICE MODE
    MenuButtonId_1801   ,       ///YES
    MenuButtonId_1802   ,       ///NO
    MenuButtonId_1803   ,       ///INFORMATION
    MenuButtonId_1804   ,       ///VERSION
    MenuButtonId_1805   ,       ///OPERATION TIME
    MenuButtonId_1806   ,       ///UPDATE
    MenuButtonId_1807   ,       ///YES
    MenuButtonId_1808   ,       ///NO
    MenuButtonId_1809   ,       ///LANGUAGE
    MenuButtonId_1810   ,       ///ì˙ñ{åÍ
    MenuButtonId_1811   ,       ///ENGLISH
    MenuButtonId_1812   ,       ///íÜï∂
    MenuButtonId_1813   ,       ///SPANISH
    MenuButtonId_1814   ,       ///FRENCH
    MenuButtonId_1815   ,       ///GERMAN
    MenuButtonId_1816   ,       ///ITALIAN
    MenuButtonId_1817   ,       ///RUSSIAN
    MenuButtonId_1818   ,       ///DUTCH
    MenuButtonId_1819   ,       ///TURKISH
    MenuButtonId_1820   ,       ///SWEDISH
    MenuButtonId_1821   ,       ///POLISH
    MenuButtonId_1822   ,       ///CZECH
    MenuButtonId_1823   ,       ///HUNGARIAN
    MenuButtonId_1824   ,       ///MENU INITIALIZE
    MenuButtonId_1825   ,       ///OPTION
    MenuButtonId_1826   ,       ///AREA SETTINGS
    MenuButtonId_1827   ,       ///AREA 1
    MenuButtonId_1828   ,       ///AREA 2
    MenuButtonId_1829   ,       ///AREA 3
    MenuButtonId_1830   ,       ///AREA 4
    MenuButtonId_1831   ,       ///Fact
    MenuButtonId_1832   ,       ///0
    MenuButtonId_1833   ,       ///1
    MenuButtonId_1834   ,       ///YES
    MenuButtonId_1835   ,       ///NO
    MenuButtonId_1836   ,       ///2
    MenuButtonId_1837   ,       ///4
    MenuButtonId_1838   ,       ///7
    MenuButtonId_1839   ,       ///ON
    MenuButtonId_1840   ,       ///OFF
    MenuButtonId_1841   ,       ///16
    MenuButtonId_1842   ,       ///21
    MenuButtonId_1843   ,       ///22
    MenuButtonId_1844   ,       ///GRADE1
    MenuButtonId_1845   ,       ///GRADE2
    MenuButtonId_Max,
} CtMenuButtonId;
#endif /* _CT_MENU_BUTTON_ID_H_ */

