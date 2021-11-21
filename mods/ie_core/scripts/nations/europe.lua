-----------------------------------------------------------------------
-- Europe (excluding balkans, scandinavia and the mess that Germany was)
-- Initial nations
united_kingdom = Nation:new{ ref_name = "united_kingdom" }
united_kingdom.name = _("United Kingdom")
united_kingdom.adjective = _("British")
united_kingdom:register()
united_kingdom:set_ideology(monarchy)
united_kingdom:add_accepted_culture(british)
united_kingdom:add_accepted_culture(irish)
united_kingdom:add_client_hint(monarchy, _("United Kingdom"), 0xc94c40)

netherlands = Nation:new{ ref_name = "netherlands" }
netherlands.name = _("Netherlands")
netherlands.adjective = _("Dutch")
netherlands:register()
netherlands:set_ideology(monarchy)
netherlands:add_accepted_culture(dutch)
netherlands:add_client_hint(monarchy, _("Netherlands"), 0xf5931b)

france = Nation:new{ ref_name = "france" }
france.name = _("France")
france.adjective = _("French")
france.combo_form = _("Franco")
france:register()
france:set_ideology(monarchy)
france:add_accepted_culture(french)
france:add_client_hint(monarchy, _("France"), 0x1b3cb3)

spain = Nation:new{ ref_name = "spain" }
spain.name = _("Spain")
spain.adjective = _("Spanish")
spain.noun = _("Spainiard")
spain:register()
spain:set_ideology(monarchy)
spain:add_accepted_culture(spanish)
spain:add_client_hint(monarchy, _("Spain"), 0xdee03a)

portugal = Nation:new{ ref_name = "portugal" }
portugal.name = _("Portugal")
portugal.adjective = _("Portuguese")
portugal:register()
portugal:set_ideology(monarchy)
portugal:add_accepted_culture(portuguese)
portugal:add_client_hint(monarchy, _("Portugal"), 0x0f691f)
portugal:add_client_hint(communism, _("People's Republic of Portugal"), 0x0f691f)

-- Formable nations
european_union = Nation:new{ ref_name = "european_union" }
european_union.name = _("European Union")
european_union.adjective = _("European")
european_union:register()
european_union:add_accepted_culture(catalan)
european_union:add_accepted_culture(basque)
european_union:add_accepted_culture(galician)
european_union:add_accepted_culture(aragonese)
european_union:add_accepted_culture(portuguese)
european_union:add_accepted_culture(spanish)
european_union:add_accepted_culture(german)
european_union:add_accepted_culture(polish)
european_union:add_accepted_culture(czech)
european_union:add_accepted_culture(slovakian)
european_union:add_accepted_culture(french)
european_union:add_accepted_culture(italian)
european_union:add_accepted_culture(greek)
european_union:add_accepted_culture(danish)
european_union:add_accepted_culture(british)
european_union:add_accepted_culture(irish)
european_union:add_accepted_culture(portuguese)
european_union:add_accepted_culture(hungarian)
european_union:add_client_hint(democracy, _("European Union"), 0x060666)
european_union:add_client_hint(communism, _("European Commune"), 0x060666)

iberia = Nation:new{ ref_name = "iberia" }
iberia.name = _("Iberia")
iberia.adjective = _("Iberian")
iberia:register()
iberia:add_accepted_culture(catalan)
iberia:add_accepted_culture(basque)
iberia:add_accepted_culture(galician)
iberia:add_accepted_culture(aragonese)
iberia:add_accepted_culture(portuguese)
iberia:add_accepted_culture(spanish)
iberia:add_client_hint(communism, _("Iberia"), 0x808000)

-- Releasable nations
brittany = Nation:new{ ref_name = "brittany" }
brittany.name = _("Brittany")
brittany:register()
brittany:add_client_hint(communism, _("Brittany"), 0x808000)

normandy = Nation:new{ ref_name = "normandy" }
normandy.name = _("Normandy")
normandy:register()
normandy:add_client_hint(communism, _("Normandy"), 0x808000)

occitania = Nation:new{ ref_name = "occitania"}
occitania.name = _("Occitania")
occitania:register()
occitania:add_client_hint(communism, _("Occitania"), 0x808000)

catalonia = Nation:new{ ref_name = "catalonia" }
catalonia.name = _("Catalonia")
catalonia.adjective = _("Catalonian")
catalonia:register()
catalonia:add_client_hint(republic, _("Catalonia"), 0xeda65a)

catalonia:add_accepted_culture(catalan)
basque_country = Nation:new{ ref_name = "basque" }
basque_country.name = _("Basque")
basque_country.adjective = _("Basque")
basque_country:register()
basque_country:add_client_hint(communism, _("Basque"), 0x808000)

basque_country:add_accepted_culture(basque)
galicia = Nation:new{ ref_name = "galicia" }
galicia.name = _("Galicia")
galicia.adjective = _("Galician")
galicia:register()
galicia:add_client_hint(communism, _("Galicia"), 0x808000)

galicia:add_accepted_culture(galician)
aragon = Nation:new{ ref_name = "aragon" }
aragon.name = _("Aragon")
aragon.adjective = _("Aragonesse")
aragon:register()
aragon:add_accepted_culture(aragonese)
aragon:add_client_hint(communism, _("Aragon"), 0x808000)

-- Formable by both czech and slovakia
czechoslovakia = Nation:new{ ref_name = "czechoslovakia" }
czechoslovakia.name = _("Czechoslovakia")
czechoslovakia.adjective = _("Czechoslovak")
czechoslovakia:register()
czechoslovakia:add_accepted_culture(slovakian)
czechoslovakia:add_accepted_culture(czech)
czechoslovakia:add_client_hint(communism, _("Czechoslovakia"), 0x384a8a)
-----------------------------------------------------------------------

-----------------------------------------------------------------------
-- Scandinavia
-- Initial nations
denmark = Nation:new{ ref_name = "denmark" }
denmark.name = _("Denmark")
denmark.adjective = _("Danish")
denmark:register()
denmark:set_ideology(monarchy)
denmark:add_accepted_culture(danish)
denmark:add_client_hint(monarchy, _("Denmark"), 0xc27b6d)

sweden = Nation:new{ ref_name = "sweden" }
sweden.name = _("Sweden")
sweden.adjective = _("Swedish")
sweden.noun = _("Swede")
sweden:register()
sweden:set_ideology(monarchy)
sweden:add_accepted_culture(swedish)
sweden:add_client_hint(monarchy, _("Sweden"), 0x3a739e)

-- Formable nations
scandinavia = Nation:new{ ref_name = "scandinavia" }
scandinavia.name = _("Scandinavia")
scandinavia.adjective = _("Scandinavian")
scandinavia:register()
scandinavia:set_ideology(monarchy)
scandinavia:add_accepted_culture(finnish)
scandinavia:add_accepted_culture(norwegian)
scandinavia:add_accepted_culture(swedish)
scandinavia:add_accepted_culture(danish)
scandinavia:add_client_hint(monarchy, _("Scandinavia"), 0x3a739e)

-- Releasable nations
finland = Nation:new{ ref_name = "finland" }
finland.name = _("Finland")
finland.adjective = _("Finnish")
finland.combo_form = _("Finno")
finland:register()
finland:add_accepted_culture(finnish)
finland:add_client_hint(monarchy, _("Finland"), 0xb9ebeb)

norway = Nation:new{ ref_name = "norway" }
norway.name = _("Norway")
norway.adjective = _("Norwegian")
norway:register()
norway:add_accepted_culture(norwegian)
norway:add_client_hint(monarchy, _("Norway"), 0xab1659)

aland = Nation:new{ ref_name = "aland" }
aland.name = _("Åland")
aland:register()
aland:add_accepted_culture(finnish)
aland:add_accepted_culture(swedish)
aland:add_client_hint(monarchy, _("Åland"), 0xe6dd45)

iceland = Nation:new{ ref_name = "iceland" }
iceland.name = _("Iceland")
iceland.adjective = _("Icelandic")
iceland:register()
iceland:add_accepted_culture(icelandic)
iceland:add_client_hint(monarchy, _("Iceland"), 0x8293d1)
-----------------------------------------------------------------------

-----------------------------------------------------------------------
-- Poland, Baltics and European Russia
-- Initial nations
russia = Nation:new{ ref_name = "russia" }
russia.name = _("Russia")
russia.adjective = _("Russian")
russia.combo_form = _("Russo")
russia:register()
russia:set_ideology(monarchy)
russia:add_accepted_culture(russian)
russia:add_client_hint(monarchy, _("Russian Empire"), 0x318c23)
russia:add_client_hint(communism, _("Russian SFSR"), 0xbf0000)

krakow = Nation:new{ ref_name = "krakow" }
krakow.name = _("Krakow")
krakow:register()
krakow:set_ideology(monarchy)
krakow:add_accepted_culture(polish)
krakow:add_client_hint(communism, _("Krakow"), 0xe6f4f7)

-- Releasable nations
-- Poland can be formed by krakow
poland = Nation:new{ ref_name = "poland" }
poland.name = _("Poland")
poland.adjective = _("Polish")
poland:register()
poland:add_accepted_culture(polish)
poland:add_client_hint(communism, _("Poland"), 0xbf85d6)
poland:add_client_hint(monarchy, _("Poland"), 0xbf85d6)
poland:add_client_hint(republic, _("Poland"), 0xbf85d6)

lithuania = Nation:new{ ref_name = "lithuania" }
lithuania.name = _("Lithuania")
lithuania.adjective = _("Lithuanian")
lithuania:register()
lithuania:add_accepted_culture(lithuanian)
lithuania:add_client_hint(republic, _("Lithuania"), 0x598c42)
lithuania:add_client_hint(monarchy, _("Lithuania SFSR"), 0x598c42)

estonia = Nation:new{ ref_name = "estonia" }
estonia.name = _("Estonia")
estonia.adjective = _("Estonian")
estonia:register()
estonia:add_accepted_culture(estonian)
estonia:add_client_hint(republic, _("Estonia"), 0x4c8ed4)
estonia:add_client_hint(monarchy, _("Estonia SFSR"), 0x4c8ed4)

latvia = Nation:new{ ref_name = "latvia" }
latvia.name = _("Latvia")
latvia.adjective = _("Latvian")
latvia:register()
latvia:add_accepted_culture(latvian)
latvia:add_client_hint(republic, _("Latvia"), 0x962820)
latvia:add_client_hint(monarchy, _("Latvia SFSR"), 0x962820)

-- Lovonia can be formed by either latvia, estonia or lithuania
livonia = Nation:new{ ref_name = "livonia" }
livonia.name = _("Livonia")
livonia.adjective = _("Livonian")
livonia:register()
livonia:add_accepted_culture(lithuanian)
livonia:add_accepted_culture(latvian)
livonia:add_accepted_culture(estonian)
livonia:add_client_hint(monarchy, _("Livonia"), 0x69917f)

romania = Nation:new{ ref_name = "romania" }
romania.name = _("Romania")
romania.adjective = _("Romanian")
romania:register()
romania:add_accepted_culture(bulgarian)
romania:add_client_hint(monarchy, _("Romania"), 0xcfa85b)

bulgaria = Nation:new{ ref_name = "bulgaria" }
bulgaria.name = _("Bulgaria")
bulgaria.adjective = _("Bulgarian")
bulgaria:register()
bulgaria:add_accepted_culture(bulgarian)
bulgaria:add_client_hint(monarchy, _("Bulgaria"), 0x78cf7d)

muscovy = Nation:new{ ref_name = "muscovy" }
muscovy.name = _("Muscovy")
muscovy:register()
muscovy:add_accepted_culture(russian)
muscovy:add_client_hint(communism, _("Muscovy"), 0x808000)

great_horde = Nation:new{ ref_name = "great_horde" }
great_horde.name = _("Great Horde")
great_horde:register()
great_horde:add_accepted_culture(turkish)
great_horde:add_client_hint(communism, _("Great Horde"), 0x808000)

novgorod = Nation:new{ ref_name = "novgorod" }
novgorod.name = _("Novgorod")
novgorod:register()
novgorod:add_accepted_culture(russian)
novgorod:add_accepted_culture(finnish)
novgorod:add_client_hint(communism, _("Novgorod"), 0x808000)

nogai_horde = Nation:new{ ref_name = "nogai_horde" }
nogai_horde.name = _("Nogai Horde")
nogai_horde.adjective = _("Nogai")
nogai_horde:register()
nogai_horde:add_accepted_culture(nogai)
nogai_horde:add_client_hint(communism, _("Nogai Horde"), 0x808000)

uzbekistan = Nation:new{ ref_name = "uzbekistan" }
uzbekistan.name = _("Uzbekistan")
uzbekistan.adjective = _("Uzbek")
uzbekistan:register()
uzbekistan:add_accepted_culture(uzbek)
uzbekistan:add_client_hint(communism, _("Uzbekistan"), 0x808000)

kazakhistan = Nation:new{ ref_name = "kazakhistan" }
kazakhistan.name = _("Kazakhistan")
kazakhistan.adjective = _("Kazakh")
kazakhistan:register()
kazakhistan:add_accepted_culture(kazakh)
kazakhistan:add_client_hint(monarchy, _("Kazakhistan"), 0x2276b3)

kyrgyztan = Nation:new{ ref_name = "kyrgyztan" }
kyrgyztan.name = _("Kyrgyztan")
kyrgyztan.adjective = _("Kyrgyz")
kyrgyztan:register()
kyrgyztan:add_accepted_culture(kyrgyz)
kyrgyztan:add_client_hint(monarchy, _("Kyrgyztan"), 0xc44f45)
kyrgyztan:add_client_hint(communism, _("Kyrgyztan"), 0xc44f45)

afghanistan = Nation:new{ ref_name = "afghanistan" }
afghanistan.name = _("Afghanistan")
afghanistan.adjective = _("Afghan")
afghanistan.noun = _("Afghani")
afghanistan:register()
afghanistan:add_accepted_culture(afghan)
afghanistan:add_client_hint(monarchy, _("Afghanistan"), 0x3b6b48)
-----------------------------------------------------------------------

-----------------------------------------------------------------------
-- Holy Roman Empire (German part)
-- Initial nations
prussia = Nation:new{ ref_name = "prussia" }
prussia.name = _("Prussia")
prussia.adjective = _("Prussian")
prussia:register()
prussia:set_ideology(democracy)
prussia:add_accepted_culture(german)
prussia:add_client_hint(monarchy, _("Prussia"), 0x405370)

salzburg = Nation:new{ ref_name = "salzburg" }
salzburg.name = _("Salzburg")
salzburg:register()
salzburg:set_ideology(democracy)
salzburg:add_accepted_culture(german)
salzburg:add_client_hint(monarchy, _("Salzburg"), 0x808000)

saxony = Nation:new{ ref_name = "saxony" }
saxony.name = _("Saxony")
saxony:register()
saxony:set_ideology(democracy)
saxony:add_accepted_culture(german)
saxony:add_client_hint(monarchy, _("Saxony"), 0x808000)

lorraine = Nation:new{ ref_name = "lorraine" }
lorraine.name = _("Lorraine")
lorraine:register()
lorraine:set_ideology(democracy)
lorraine:add_accepted_culture(german)
lorraine:add_accepted_culture(french)
lorraine:add_client_hint(monarchy, _("Lorraine"), 0x808000)

brandenburg = Nation:new{ ref_name = "brandenburg" }
brandenburg.name = _("Brandenburg")
brandenburg:register()
brandenburg:set_ideology(democracy)
brandenburg:add_accepted_culture(german)
brandenburg:add_client_hint(monarchy, _("Brandenburg"), 0x808000)

frankfurt = Nation:new{ ref_name = "frankfurt" }
frankfurt.name = _("Frankfurt")
frankfurt:register()
frankfurt:set_ideology(democracy)
frankfurt:add_accepted_culture(german)
frankfurt:add_client_hint(monarchy, _("Frankfurt"), 0x808000)

munich = Nation:new{ ref_name = "munich" }
munich.name = _("Munich")
munich:register()
munich:set_ideology(democracy)
munich:add_accepted_culture(german)
munich:add_client_hint(monarchy, _("Munich"), 0x808000)

holstein = Nation:new{ ref_name = "holstein" }
holstein.name = _("Holstein")
holstein:register()
holstein:set_ideology(democracy)
holstein:add_accepted_culture(german)
holstein:add_accepted_culture(danish)
holstein:add_client_hint(monarchy, _("Holstein"), 0x808000)

bavaria = Nation:new{ ref_name = "bavaria" }
bavaria.name = _("Bavaria")
bavaria:register()
bavaria:set_ideology(democracy)
bavaria:add_accepted_culture(german)
bavaria:add_client_hint(monarchy, _("Bavaria"), 0x808000)

switerzeland = Nation:new{ ref_name = "switerzeland" }
switerzeland.name = _("Switerzeland")
switerzeland:register()
switerzeland:set_ideology(democracy)
switerzeland:add_accepted_culture(french)
switerzeland:add_accepted_culture(german)
switerzeland:add_accepted_culture(italian)
switerzeland:add_client_hint(monarchy, _("Switerzeland"), 0xb32609)

hannover = Nation:new{ ref_name = "hannover" }
hannover.name = _("Hannover")
hannover:register()
hannover:set_ideology(democracy)
hannover:add_accepted_culture(german)
hannover:add_client_hint(communism, _("Hannover"), 0x808000)

luxembourg = Nation:new{ ref_name = "luxembourg" }
luxembourg.name = _("Luxembourg")
luxembourg:register()
luxembourg:set_ideology(democracy)
luxembourg:add_accepted_culture(french)
luxembourg:add_accepted_culture(german)
luxembourg:add_client_hint(monarchy, _("Luxembourg"), 0x45d1ca)

nassau = Nation:new{ ref_name = "nassau" }
nassau.name = _("Nassau")
nassau:register()
nassau:set_ideology(democracy)
nassau:add_accepted_culture(german)
nassau:add_client_hint(communism, _("Nassau"), 0x808000)

baden = Nation:new{ ref_name = "baden" }
baden.name = _("Baden")
baden:register()
baden:set_ideology(democracy)
baden:add_accepted_culture(german)
baden:add_client_hint(communism, _("Baden"), 0x808000)

anhalt = Nation:new{ ref_name = "anhalt" }
anhalt.name = _("Anhalt")
anhalt:register()
anhalt:set_ideology(democracy)
anhalt:add_accepted_culture(german)
anhalt:add_client_hint(communism, _("Anhalt"), 0x808000)

silesia = Nation:new{ ref_name = "silesia" }
silesia.name = _("Silesia")
silesia:register()
silesia:set_ideology(democracy)
silesia:add_accepted_culture(polish)
silesia:add_accepted_culture(german)
silesia:add_client_hint(communism, _("Silesia"), 0x808000)

danzig = Nation:new{ ref_name = "danzig" }
danzig.name = _("Danzig")
danzig:register()
danzig:set_ideology(democracy)
danzig:add_accepted_culture(german)
danzig:add_client_hint(communism, _("Danzig"), 0x808000)

wurttemberg = Nation:new{ ref_name = "wurttemberg" }
wurttemberg.name = _("Württemberg")
wurttemberg:register()
wurttemberg:set_ideology(democracy)
wurttemberg:add_accepted_culture(german)
wurttemberg:add_client_hint(communism, _("Württemberg"), 0x808000)

austria = Nation:new{ ref_name = "austria" }
austria.name = _("Austria")
austria.adjective = _("Austrian")
austria.combo_form = _("Austro")
austria:register()
austria:set_ideology(democracy)
austria:add_accepted_culture(german)
austria:add_client_hint(monarchy, _("Austria"), 0xe8ebe8)
austria:add_client_hint(republic, _("Austria"), 0xe8ebe8)

-- Releasable nations
hungary = Nation:new{ ref_name = "hungary" }
hungary.name = _("Hungary")
hungary.adjective = _("Hungarian")
hungary:register()
hungary:set_ideology(monarchy)
hungary:add_accepted_culture(hungarian)
hungary:add_client_hint(communism, _("People's Republic of Hungary"), 0x3f7051)
hungary:add_client_hint(monarchy, _("Hungary"), 0x3f7051)
hungary:add_client_hint(republic, _("Hungary"), 0x3f7051)

-- Formable nations
greater_prussia = Nation:new{ ref_name = "greater_prussia" }
greater_prussia.name = _("Greater Prussia")
greater_prussia.adjective = _("Prussian")
greater_prussia:register()
greater_prussia:add_accepted_culture(german)
greater_prussia:add_client_hint(communism, _("Greater Prussia"), 0x808000)

germany = Nation:new{ ref_name = "germany" }
germany.name = _("Germany")
germany.adjective = _("German")
germany:register()
germany:add_accepted_culture(german)
germany:add_client_hint(communism, _("Germany"), 0x6e6e6e)

holy_roman_empire = Nation:new{ ref_name = "holy_roman_empire" }
holy_roman_empire.name = _("Holy Roman Empire")
holy_roman_empire:register()
holy_roman_empire:add_accepted_culture(german)
holy_roman_empire:add_accepted_culture(italian)
holy_roman_empire:add_client_hint(monarchy, _("Holy Roman Empire"), 0xf0e930)

roman_empire = Nation:new{ ref_name = "roman_empire" }
roman_empire.name = _("Roman Empire")
roman_empire.adjective = _("Roman")
roman_empire:register()
roman_empire:add_accepted_culture(italian)
roman_empire:add_client_hint(communism, _("Roman Empire"), 0x808000)

austria_hungary = Nation:new{ ref_name = "austria_hungary" }
austria_hungary.name = _("Austria-Hungary")
austria_hungary.adjective = _("Austro-Hungarian")
austria_hungary:register()
austria_hungary:add_accepted_culture(german)
austria_hungary:add_accepted_culture(hungarian)
austria_hungary:add_client_hint(monarchy, _("Austria-Hungary"), 0xe8ebe8)
-----------------------------------------------------------------------

-----------------------------------------------------------------------
-- Holy Roman Empire (Italian part)
-- Initial nations

venice = Nation:new{ ref_name = "venice" }
venice.name = _("Venice")
venice.adjective = _("Venetian")
venice:register()
venice:set_ideology(democracy)
venice:add_accepted_culture(italian)
venice:add_client_hint(republic, _("Venice"), 0x808000)

genoa = Nation:new{ ref_name = "genoa" }
genoa.name = _("Genoa")
genoa:register()
genoa:set_ideology(democracy)
genoa:add_accepted_culture(italian)
genoa:add_client_hint(monarchy, _("Genoa"), 0x808000)

papal_states = Nation:new{ ref_name = "papal_states" }
papal_states.name = _("Papal states")
papal_states:register()
papal_states:set_ideology(democracy)
papal_states:add_accepted_culture(italian)
papal_states:add_client_hint(monarchy, _("Papal states"), 0xf7f6cd)

piedmont_sardinia = Nation:new{ ref_name = "piedmont_sardinia" }
piedmont_sardinia.name = _("Piedmont-Sardinia")
piedmont_sardinia:register()
piedmont_sardinia:set_ideology(democracy)
piedmont_sardinia:add_accepted_culture(italian)
piedmont_sardinia:add_client_hint(monarchy, _("Piedmont-Sardinia"), 0x808000)

two_sicilies = Nation:new{ ref_name = "two_sicilies" }
two_sicilies.name = _("Two Sicilies")
two_sicilies:register()
two_sicilies:set_ideology(democracy)
two_sicilies:add_accepted_culture(italian)
two_sicilies:add_client_hint(monarchy, _("Two Sicilies"), 0x808000)

tuscany = Nation:new{ ref_name = "tuscany" }
tuscany.name = _("Tuscany")
tuscany:register()
tuscany:set_ideology(democracy)
tuscany:add_accepted_culture(italian)
tuscany:add_client_hint(monarchy, _("Tuscany"), 0x808000)

savoie = Nation:new{ ref_name = "savoie" }
savoie.name = _("Savoie")
savoie:register()
savoie:set_ideology(democracy)
savoie:add_accepted_culture(italian)
savoie:add_client_hint(monarchy, _("Savoie"), 0x808000)

-- Formable nations
italy = Nation:new{ ref_name = "italy" }
italy.name = _("Italy")
italy.adjective = _("Italian")
italy:register()
italy:add_accepted_culture(italian)
italy:add_client_hint(monarchy, _("Italy"), 0x5fbf5c)
italy:add_client_hint(republic, _("Italy"), 0x5fbf5c)

-----------------------------------------------------------------------

-----------------------------------------------------------------------
-- Balkans
turkey = Nation:new{ ref_name = "turkey" }
turkey.name = _("Turkey")
turkey.adjective = _("Turkish")
turkey.noun = _("Turk")
turkey.combo_form = _("Turco")
turkey:register()
turkey:set_ideology(monarchy)
turkey:add_accepted_culture(turkish)
chile:add_client_hint(monarchy, _("Turkey"), 0xc9201a)
chile:add_client_hint(republic, _("Turkey"), 0xc9201a)

greece = Nation:new{ ref_name = "greece" }
greece.name = _("Greece")
greece.adjective = _("Greek")
greece.combo_form = _("Greco")
greece:register()
greece:set_ideology(monarchy)
greece:add_accepted_culture(greek)
greece:add_client_hint(monarchy, _("Greece"), 0xaac4e6)

-- Releasable nations
kosovo = Nation:new{ ref_name = "kosovo" }
kosovo.name = _("Kosovo")
kosovo:register()
kosovo:add_client_hint(communism, _("Kosovo"), 0x808000)

bosnia_and_herzegovina = Nation:new{ ref_name = "bosnia_and_herzegovina" }
bosnia_and_herzegovina.name = _("Bosnia and Herzegovina")
bosnia_and_herzegovina:register()
bosnia_and_herzegovina:add_client_hint(communism, _("Bosnia and Herzegovina"), 0x808000)
-----------------------------------------------------------------------
