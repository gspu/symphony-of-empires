--------------------------------------------------------------
-- Continent: Europe
-- Subcontinent: Balkans
-- Country: Austrian Empire
province = Province:new{ ref_name = "prague", color = 0xf460ff }
province.name = _("Prague")
province:register()
province:add_industry(wheat_farm, united_states)
province:add_pop(artisan, czech, catholic, 50000, 0.9)
province:add_pop(farmer, czech, catholic, 400000, 0.8)
province:add_pop(soldier, czech, catholic, 80000, 0.8)
province:add_pop(craftsmen, czech, catholic, 50000, 0.9)
province:add_pop(bureaucrat, czech, catholic, 50000, 0.9)
province:add_pop(burgeoise, czech, catholic, 50000, 0.9)
province:add_pop(clergymen, czech, catholic, 50000, 0.9)
province:add_pop(laborer, czech, catholic, 500000, 0.8)
province:add_pop(burgeoise, czech, catholic, 8000, 0.9)
province:add_pop(artisan, slovakian, catholic, 50000, 0.9)
province:add_pop(farmer, slovakian, catholic, 400000, 0.8)
province:add_pop(soldier, slovakian, catholic, 80000, 0.8)
province:add_pop(craftsmen, slovakian, catholic, 50000, 0.9)
province:add_pop(bureaucrat, slovakian, catholic, 50000, 0.9)
province:add_pop(burgeoise, slovakian, catholic, 50000, 0.9)
province:add_pop(clergymen, slovakian, catholic, 50000, 0.9)
province:add_pop(laborer, slovakian, catholic, 500000, 0.8)
province:add_pop(burgeoise, slovakian, catholic, 8000, 0.9)
province:add_pop(artisan, german, catholic, 5000, 0.9)
province:add_pop(farmer, german, catholic, 40000, 0.8)
province:add_pop(soldier, german, catholic, 8000, 0.8)
province:add_pop(craftsmen, german, catholic, 5000, 0.9)
province:add_pop(bureaucrat, german, catholic, 5000, 0.9)
province:add_pop(burgeoise, german, catholic, 5000, 0.9)
province:add_pop(clergymen, german, catholic, 5000, 0.9)
province:add_pop(laborer, german, catholic, 50000, 0.8)
province:add_pop(burgeoise, german, catholic, 800, 0.9)
province:add_pop(artisan, hungarian, catholic, 5000, 0.9)
province:add_pop(farmer, hungarian, catholic, 40000, 0.8)
province:add_pop(soldier, hungarian, catholic, 8000, 0.8)
province:add_pop(craftsmen, hungarian, catholic, 5000, 0.9)
province:add_pop(bureaucrat, hungarian, catholic, 5000, 0.9)
province:add_pop(burgeoise, hungarian, catholic, 5000, 0.9)
province:add_pop(clergymen, hungarian, catholic, 5000, 0.9)
province:add_pop(laborer, hungarian, catholic, 50000, 0.8)
province:add_pop(burgeoise, hungarian, catholic, 800, 0.9)
province:add_nucleus(austria)
province:add_nucleus(czechoslovakia)
province:give_to(austria)
czechoslovakia:set_capital(province)

province = Province:new{ ref_name = "north_bohemia", color = 0xff72bd }
province.name = _("North Bohemia")
province:register()
province:add_industry(wheat_farm, united_states)
province:add_pop(artisan, czech, catholic, 5000, 0.9)
province:add_pop(farmer, czech, catholic, 40000, 0.8)
province:add_pop(soldier, czech, catholic, 8000, 0.8)
province:add_pop(craftsmen, czech, catholic, 5000, 0.9)
province:add_pop(bureaucrat, czech, catholic, 5000, 0.9)
province:add_pop(burgeoise, czech, catholic, 5000, 0.9)
province:add_pop(clergymen, czech, catholic, 5000, 0.9)
province:add_pop(laborer, czech, catholic, 50000, 0.8)
province:add_pop(burgeoise, czech, catholic, 800, 0.9)
province:add_pop(artisan, slovakian, catholic, 5000, 0.9)
province:add_pop(farmer, slovakian, catholic, 40000, 0.8)
province:add_pop(soldier, slovakian, catholic, 8000, 0.8)
province:add_pop(craftsmen, slovakian, catholic, 5000, 0.9)
province:add_pop(bureaucrat, slovakian, catholic, 5000, 0.9)
province:add_pop(burgeoise, slovakian, catholic, 5000, 0.9)
province:add_pop(clergymen, slovakian, catholic, 5000, 0.9)
province:add_pop(laborer, slovakian, catholic, 50000, 0.8)
province:add_pop(burgeoise, slovakian, catholic, 800, 0.9)
province:add_pop(artisan, german, catholic, 5000, 0.9)
province:add_pop(farmer, german, catholic, 40000, 0.8)
province:add_pop(soldier, german, catholic, 8000, 0.8)
province:add_pop(craftsmen, german, catholic, 5000, 0.9)
province:add_pop(bureaucrat, german, catholic, 5000, 0.9)
province:add_pop(burgeoise, german, catholic, 5000, 0.9)
province:add_pop(clergymen, german, catholic, 5000, 0.9)
province:add_pop(laborer, german, catholic, 50000, 0.8)
province:add_pop(burgeoise, german, catholic, 800, 0.9)
province:add_pop(artisan, hungarian, catholic, 5000, 0.9)
province:add_pop(farmer, hungarian, catholic, 40000, 0.8)
province:add_pop(soldier, hungarian, catholic, 8000, 0.8)
province:add_pop(craftsmen, hungarian, catholic, 5000, 0.9)
province:add_pop(bureaucrat, hungarian, catholic, 5000, 0.9)
province:add_pop(burgeoise, hungarian, catholic, 5000, 0.9)
province:add_pop(clergymen, hungarian, catholic, 5000, 0.9)
province:add_pop(laborer, hungarian, catholic, 50000, 0.8)
province:add_pop(burgeoise, hungarian, catholic, 800, 0.9)
province:add_nucleus(austria)
province:add_nucleus(czechoslovakia)
province:give_to(austria)

province = Province:new{ ref_name = "south_moravia", color = 0xff9b87 }
province.name = _("South Moravia")
province:register()
province:add_industry(wheat_farm, united_states)
province:add_pop(artisan, czech, catholic, 5000, 0.9)
province:add_pop(farmer, czech, catholic, 40000, 0.8)
province:add_pop(soldier, czech, catholic, 8000, 0.8)
province:add_pop(craftsmen, czech, catholic, 5000, 0.9)
province:add_pop(bureaucrat, czech, catholic, 5000, 0.9)
province:add_pop(burgeoise, czech, catholic, 5000, 0.9)
province:add_pop(clergymen, czech, catholic, 5000, 0.9)
province:add_pop(laborer, czech, catholic, 50000, 0.8)
province:add_pop(burgeoise, czech, catholic, 800, 0.9)
province:add_pop(artisan, slovakian, catholic, 5000, 0.9)
province:add_pop(farmer, slovakian, catholic, 40000, 0.8)
province:add_pop(soldier, slovakian, catholic, 8000, 0.8)
province:add_pop(craftsmen, slovakian, catholic, 5000, 0.9)
province:add_pop(bureaucrat, slovakian, catholic, 5000, 0.9)
province:add_pop(burgeoise, slovakian, catholic, 5000, 0.9)
province:add_pop(clergymen, slovakian, catholic, 5000, 0.9)
province:add_pop(laborer, slovakian, catholic, 50000, 0.8)
province:add_pop(burgeoise, slovakian, catholic, 800, 0.9)
province:add_pop(artisan, german, catholic, 5000, 0.9)
province:add_pop(farmer, german, catholic, 40000, 0.8)
province:add_pop(soldier, german, catholic, 8000, 0.8)
province:add_pop(craftsmen, german, catholic, 5000, 0.9)
province:add_pop(bureaucrat, german, catholic, 5000, 0.9)
province:add_pop(burgeoise, german, catholic, 5000, 0.9)
province:add_pop(clergymen, german, catholic, 5000, 0.9)
province:add_pop(laborer, german, catholic, 50000, 0.8)
province:add_pop(burgeoise, german, catholic, 800, 0.9)
province:add_pop(artisan, hungarian, catholic, 5000, 0.9)
province:add_pop(farmer, hungarian, catholic, 40000, 0.8)
province:add_pop(soldier, hungarian, catholic, 8000, 0.8)
province:add_pop(craftsmen, hungarian, catholic, 5000, 0.9)
province:add_pop(bureaucrat, hungarian, catholic, 5000, 0.9)
province:add_pop(burgeoise, hungarian, catholic, 5000, 0.9)
province:add_pop(clergymen, hungarian, catholic, 5000, 0.9)
province:add_pop(laborer, hungarian, catholic, 50000, 0.8)
province:add_pop(burgeoise, hungarian, catholic, 800, 0.9)
province:add_nucleus(austria)
province:add_nucleus(czechoslovakia)
province:give_to(austria)

province = Province:new{ ref_name = "moravia", color = 0x6e42ff }
province.name = _("Moravia")
province:register()
province:add_industry(wheat_farm, united_states)
province:add_pop(artisan, czech, catholic, 5000, 0.9)
province:add_pop(farmer, czech, catholic, 40000, 0.8)
province:add_pop(soldier, czech, catholic, 8000, 0.8)
province:add_pop(craftsmen, czech, catholic, 5000, 0.9)
province:add_pop(bureaucrat, czech, catholic, 5000, 0.9)
province:add_pop(burgeoise, czech, catholic, 5000, 0.9)
province:add_pop(clergymen, czech, catholic, 5000, 0.9)
province:add_pop(laborer, czech, catholic, 50000, 0.8)
province:add_pop(burgeoise, czech, catholic, 800, 0.9)
province:add_pop(artisan, slovakian, catholic, 5000, 0.9)
province:add_pop(farmer, slovakian, catholic, 40000, 0.8)
province:add_pop(soldier, slovakian, catholic, 8000, 0.8)
province:add_pop(craftsmen, slovakian, catholic, 5000, 0.9)
province:add_pop(bureaucrat, slovakian, catholic, 5000, 0.9)
province:add_pop(burgeoise, slovakian, catholic, 5000, 0.9)
province:add_pop(clergymen, slovakian, catholic, 5000, 0.9)
province:add_pop(laborer, slovakian, catholic, 50000, 0.8)
province:add_pop(burgeoise, slovakian, catholic, 800, 0.9)
province:add_pop(artisan, german, catholic, 5000, 0.9)
province:add_pop(farmer, german, catholic, 40000, 0.8)
province:add_pop(soldier, german, catholic, 8000, 0.8)
province:add_pop(craftsmen, german, catholic, 5000, 0.9)
province:add_pop(bureaucrat, german, catholic, 5000, 0.9)
province:add_pop(burgeoise, german, catholic, 5000, 0.9)
province:add_pop(clergymen, german, catholic, 5000, 0.9)
province:add_pop(laborer, german, catholic, 50000, 0.8)
province:add_pop(burgeoise, german, catholic, 800, 0.9)
province:add_pop(artisan, hungarian, catholic, 5000, 0.9)
province:add_pop(farmer, hungarian, catholic, 40000, 0.8)
province:add_pop(soldier, hungarian, catholic, 8000, 0.8)
province:add_pop(craftsmen, hungarian, catholic, 5000, 0.9)
province:add_pop(bureaucrat, hungarian, catholic, 5000, 0.9)
province:add_pop(burgeoise, hungarian, catholic, 5000, 0.9)
province:add_pop(clergymen, hungarian, catholic, 5000, 0.9)
province:add_pop(laborer, hungarian, catholic, 50000, 0.8)
province:add_pop(burgeoise, hungarian, catholic, 800, 0.9)
province:add_nucleus(austria)
province:add_nucleus(czechoslovakia)
province:give_to(austria)

province = Province:new{ ref_name = "north_moravia", color = 0xff6df0 }
province.name = _("North Moravia")
province:register()
province:add_industry(wheat_farm, united_states)
province:add_pop(artisan, czech, catholic, 5000, 0.9)
province:add_pop(farmer, czech, catholic, 40000, 0.8)
province:add_pop(soldier, czech, catholic, 8000, 0.8)
province:add_pop(craftsmen, czech, catholic, 5000, 0.9)
province:add_pop(bureaucrat, czech, catholic, 5000, 0.9)
province:add_pop(burgeoise, czech, catholic, 5000, 0.9)
province:add_pop(clergymen, czech, catholic, 5000, 0.9)
province:add_pop(laborer, czech, catholic, 50000, 0.8)
province:add_pop(burgeoise, czech, catholic, 800, 0.9)
province:add_pop(artisan, slovakian, catholic, 5000, 0.9)
province:add_pop(farmer, slovakian, catholic, 40000, 0.8)
province:add_pop(soldier, slovakian, catholic, 8000, 0.8)
province:add_pop(craftsmen, slovakian, catholic, 5000, 0.9)
province:add_pop(bureaucrat, slovakian, catholic, 5000, 0.9)
province:add_pop(burgeoise, slovakian, catholic, 5000, 0.9)
province:add_pop(clergymen, slovakian, catholic, 5000, 0.9)
province:add_pop(laborer, slovakian, catholic, 50000, 0.8)
province:add_pop(burgeoise, slovakian, catholic, 800, 0.9)
province:add_pop(artisan, german, catholic, 5000, 0.9)
province:add_pop(farmer, german, catholic, 40000, 0.8)
province:add_pop(soldier, german, catholic, 8000, 0.8)
province:add_pop(craftsmen, german, catholic, 5000, 0.9)
province:add_pop(bureaucrat, german, catholic, 5000, 0.9)
province:add_pop(burgeoise, german, catholic, 5000, 0.9)
province:add_pop(clergymen, german, catholic, 5000, 0.9)
province:add_pop(laborer, german, catholic, 50000, 0.8)
province:add_pop(burgeoise, german, catholic, 800, 0.9)
province:add_pop(artisan, hungarian, catholic, 5000, 0.9)
province:add_pop(farmer, hungarian, catholic, 40000, 0.8)
province:add_pop(soldier, hungarian, catholic, 8000, 0.8)
province:add_pop(craftsmen, hungarian, catholic, 5000, 0.9)
province:add_pop(bureaucrat, hungarian, catholic, 5000, 0.9)
province:add_pop(burgeoise, hungarian, catholic, 5000, 0.9)
province:add_pop(clergymen, hungarian, catholic, 5000, 0.9)
province:add_pop(laborer, hungarian, catholic, 50000, 0.8)
province:add_pop(burgeoise, hungarian, catholic, 800, 0.9)
province:add_nucleus(austria)
province:add_nucleus(czechoslovakia)
province:give_to(austria)