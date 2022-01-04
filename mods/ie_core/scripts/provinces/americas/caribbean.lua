-- Industrial_Era_mod - Base game files for Symphony of Empires
-- Copyright (C) 2021, Symphony of Empires contributors
-- 
-- This program is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation; either version 2 of the License, or
-- (at your option) any later version.
-- 
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License along
-- with this program; if not, write to the Free Software Foundation, Inc.,
-- 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
--
-- ----------------------------------------------------------------------------
--	Name:
--  	provinces/america/caribbean.lua
--
-- 	Abstract:
--      Does important stuff
-- ----------------------------------------------------------------------------

--------------------------------------------------------------
-- Continent: Americas
-- Subcontinent: Caribbean/Central America
-- Country: Kingdom of Spain
province = Province:new{ ref_name = "la_habana", color = 0xFFAEA0 }
province.name = _("Havana")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, german, protestant, 5000, 0.7)
province:add_pop(farmer, german, protestant, 5000, 0.1)
province:add_pop(soldier, german, protestant, 5000, 0.2)
province:add_pop(craftsmen, german, protestant, 5000, 0.2)
province:add_pop(bureaucrat, german, protestant, 5000, 0.7)
province:add_pop(burgeoise, german, protestant, 5000, 0.2)
province:add_pop(clergymen, german, protestant, 5000, 0.3)
province:add_pop(laborer, german, protestant, 5000, 0.2)
province:add_pop(burgeoise, german, protestant, 500, 0.9)
province:add_pop(slave, german, protestant, 500, 0.5)
province:add_nucleus(spain)
province:give_to(spain)

province = Province:new{ ref_name = "camaguey", color = 0x795BFF }
province.name = _("Camagüey")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, german, protestant, 5000, 0.7)
province:add_pop(farmer, german, protestant, 5000, 0.1)
province:add_pop(soldier, german, protestant, 5000, 0.2)
province:add_pop(craftsmen, german, protestant, 5000, 0.2)
province:add_pop(bureaucrat, german, protestant, 5000, 0.7)
province:add_pop(burgeoise, german, protestant, 5000, 0.2)
province:add_pop(clergymen, german, protestant, 5000, 0.3)
province:add_pop(laborer, german, protestant, 5000, 0.2)
province:add_pop(burgeoise, german, protestant, 500, 0.9)
province:add_pop(slave, german, protestant, 500, 0.5)
province:add_nucleus(spain)
province:give_to(spain)

province = Province:new{ ref_name = "santiago_de_cuba", color = 0xFF2197 }
province.name = _("Santiago de Cuba")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, german, protestant, 5000, 0.7)
province:add_pop(farmer, german, protestant, 5000, 0.1)
province:add_pop(soldier, german, protestant, 5000, 0.2)
province:add_pop(craftsmen, german, protestant, 5000, 0.2)
province:add_pop(bureaucrat, german, protestant, 5000, 0.7)
province:add_pop(burgeoise, german, protestant, 5000, 0.2)
province:add_pop(clergymen, german, protestant, 5000, 0.3)
province:add_pop(laborer, german, protestant, 5000, 0.2)
province:add_pop(burgeoise, german, protestant, 500, 0.9)
province:add_pop(slave, german, protestant, 500, 0.5)
province:add_nucleus(spain)
province:give_to(spain)

-- Change to Guantánamo Bay when US occupies it 
province = Province:new{ ref_name = "bahia_de_guantanamo", color = 0x7C83FF }
province.name = _("Bahía de Guantánamo")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, german, protestant, 5000, 0.7)
province:add_pop(farmer, german, protestant, 5000, 0.1)
province:add_pop(soldier, german, protestant, 5000, 0.2)
province:add_pop(craftsmen, german, protestant, 5000, 0.2)
province:add_pop(bureaucrat, german, protestant, 5000, 0.7)
province:add_pop(burgeoise, german, protestant, 5000, 0.2)
province:add_pop(clergymen, german, protestant, 5000, 0.3)
province:add_pop(laborer, german, protestant, 5000, 0.2)
province:add_pop(burgeoise, german, protestant, 500, 0.9)
province:add_pop(slave, german, protestant, 500, 0.5)
province:add_nucleus(spain)
province:give_to(spain)

province = Province:new{ ref_name = "puerto_rico", color = 0xA8FDFF }
province.name = _("Puerto Rico")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, german, protestant, 5000, 0.7)
province:add_pop(farmer, german, protestant, 5000, 0.1)
province:add_pop(soldier, german, protestant, 5000, 0.2)
province:add_pop(craftsmen, german, protestant, 5000, 0.2)
province:add_pop(bureaucrat, german, protestant, 5000, 0.7)
province:add_pop(burgeoise, german, protestant, 5000, 0.2)
province:add_pop(clergymen, german, protestant, 5000, 0.3)
province:add_pop(laborer, german, protestant, 5000, 0.2)
province:add_pop(burgeoise, german, protestant, 500, 0.9)
province:add_pop(slave, german, protestant, 500, 0.5)
province:add_nucleus(spain)
province:give_to(spain)

--------------------------------------------------------------
-- Continent: Americas
-- Subcontinent: Caribbean/Central America
-- Country: Kingdom of Denmark 

-- Rename to Saint Croix if US or France occupies, and Santa Cruz if spain occupies
province = Province:new{ ref_name = "sankt_croix", color = 0x8e2bff }
province.name = _("Sankt Croix")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, german, protestant, 5000, 0.7)
province:add_pop(farmer, german, protestant, 5000, 0.1)
province:add_pop(soldier, german, protestant, 5000, 0.2)
province:add_pop(craftsmen, german, protestant, 5000, 0.2)
province:add_pop(bureaucrat, german, protestant, 5000, 0.7)
province:add_pop(burgeoise, german, protestant, 5000, 0.2)
province:add_pop(clergymen, german, protestant, 5000, 0.3)
province:add_pop(laborer, german, protestant, 5000, 0.2)
province:add_pop(burgeoise, german, protestant, 500, 0.9)
province:add_pop(slave, german, protestant, 500, 0.5)
province:add_nucleus(denmark)
province:give_to(denmark)

--------------------------------------------------------------
-- Continent: Americas
-- Subcontinent: Caribbean/Central America
-- Country: Gran Colombia/Colombia & Venezuela respectively

province = Province:new{ ref_name = "san_andres_y_providencia", color = 0xD87FFF }
province.name = _("San Andrés y Providencia")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, german, protestant, 5000, 0.7)
province:add_pop(farmer, german, protestant, 5000, 0.1)
province:add_pop(soldier, german, protestant, 5000, 0.2)
province:add_pop(craftsmen, german, protestant, 5000, 0.2)
province:add_pop(bureaucrat, german, protestant, 5000, 0.7)
province:add_pop(burgeoise, german, protestant, 5000, 0.2)
province:add_pop(clergymen, german, protestant, 5000, 0.3)
province:add_pop(laborer, german, protestant, 5000, 0.2)
province:add_pop(burgeoise, german, protestant, 500, 0.9)
province:add_pop(slave, german, protestant, 500, 0.5)
province:add_nucleus(gran_colombia)
province:give_to(gran_colombia)

province = Province:new{ ref_name = "isla_de_margerita", color = 0xFF54D9 }
province.name = _("Isla de Margerita")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, german, protestant, 5000, 0.7)
province:add_pop(farmer, german, protestant, 5000, 0.1)
province:add_pop(soldier, german, protestant, 5000, 0.2)
province:add_pop(craftsmen, german, protestant, 5000, 0.2)
province:add_pop(bureaucrat, german, protestant, 5000, 0.7)
province:add_pop(burgeoise, german, protestant, 5000, 0.2)
province:add_pop(clergymen, german, protestant, 5000, 0.3)
province:add_pop(laborer, german, protestant, 5000, 0.2)
province:add_pop(burgeoise, german, protestant, 500, 0.9)
province:add_pop(slave, german, protestant, 500, 0.5)
province:add_nucleus(gran_colombia)
province:give_to(gran_colombia)

--------------------------------------------------------------
-- Continent: Americas
-- Subcontinent: Caribbean/Central America
-- Country: British Empire

province = Province:new{ ref_name = "jamaica", color = 0x72E9FF }
province.name = _("Jamaica")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "bahamas", color = 0x66ADFF }
province.name = _("Bahamas")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "inagua and long islands", color = 0xFFE2D8 }
province.name = _("Inagua and Long Islands")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "cayman_islands", color = 0x8CC5FF }
province.name = _("Cayman Islands")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "turks_and_caicos_islands", color = 0xFF5E89 }
province.name = _("Turks and Caicos Islands")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "virgin_islands", color = 0xFFD8E3 }
province.name = _("Virgin Islands")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "anguilla", color = 0xded1af }
province.name = _("Anguilla")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "antigua_and_barbuda", color = 0xFF5EB1 }
province.name = _("Antigua and Barbuda")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "saint_kitts_and_nevis", color = 0x99FFCD }
province.name = _("Saint Kitts and Nevis")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "dominica", color = 0xFF3AE8 }
province.name = _("Dominica")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "saint_lucia", color = 0xffb7e1 }
province.name = _("Saint Lucia")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "saint_vicent_and_the_grenadines", color = 0x87ffd5 }
province.name = _("Saint Vincent & The Grenadies")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "grenada", color = 0xFF3932 }
province.name = _("Grenada")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "barbados", color = 0xFF8EBB }
province.name = _("Barbados")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "tobago", color = 0xFFBFF7 }
province.name = _("Tobago")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

province = Province:new{ ref_name = "trinidad", color = 0x35FF6E }
province.name = _("Trinidad")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, british, protestant, 10, 0.7)
province:add_pop(farmer, british, protestant, 10, 0.1)
province:add_pop(soldier, british, protestant, 10, 0.2)
province:add_pop(craftsmen, british, protestant, 10, 0.2)
province:add_pop(bureaucrat, british, protestant, 10, 0.7)
province:add_pop(burgeoise, british, protestant, 10, 0.2)
province:add_pop(clergymen, british, protestant, 10, 0.3)
province:add_pop(laborer, british, protestant, 10, 0.2)
province:add_pop(burgeoise, british, protestant, 10, 0.9)
province:add_nucleus(united_kingdom)
province:give_to(united_kingdom)

--------------------------------------------------------------
-- Continent: Americas
-- Subcontinet: Caribbean/Central America
-- Country: Haiti

province = Province:new{ ref_name = "haiti", color = 0x72E2FF }
province.name = _("Haiti")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, haitian, catholic, 100, 0.5)
province:add_pop(farmer, haitian, catholic, 5000, 0.1)
province:add_pop(soldier, haitian, catholic, 100, 0.2)
province:add_pop(craftsmen, haitian, catholic, 100, 0.2)
province:add_pop(bureaucrat, haitian, catholic, 100, 0.6)
province:add_pop(burgeoise, haitian, catholic, 100, 0.2)
province:add_pop(clergymen, haitian, catholic, 100, 0.3)
province:add_pop(laborer, haitian, catholic, 100, 0.2)
province:add_pop(burgeoise, haitian, catholic, 100, 0.7)
province:add_nucleus(haiti)
province:give_to(haiti)
haiti:set_capital(province)

-- Rename to Hincha if conquered by the spanish/dominican republic
province = Province:new{ ref_name = "hinche", color = 0xBC49FF }
province.name = _("Hincha")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, haitian, catholic, 100, 0.5)
province:add_pop(farmer, haitian, catholic, 5000, 0.1)
province:add_pop(soldier, haitian, catholic, 100, 0.2)
province:add_pop(craftsmen, haitian, catholic, 100, 0.2)
province:add_pop(bureaucrat, haitian, catholic, 100, 0.6)
province:add_pop(burgeoise, haitian, catholic, 100, 0.2)
province:add_pop(clergymen, haitian, catholic, 100, 0.3)
province:add_pop(laborer, haitian, catholic, 100, 0.2)
province:add_pop(burgeoise, haitian, catholic, 100, 0.7)
province:add_nucleus(haiti)
province:give_to(haiti)

province = Province:new{ ref_name = "santo_domingo", color = 0xFF63B6 }
province.name = _("Santo Domingo")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, haitian, catholic, 100, 0.5)
province:add_pop(farmer, haitian, catholic, 5000, 0.1)
province:add_pop(soldier, haitian, catholic, 100, 0.2)
province:add_pop(craftsmen, haitian, catholic, 100, 0.2)
province:add_pop(bureaucrat, haitian, catholic, 100, 0.6)
province:add_pop(burgeoise, haitian, catholic, 100, 0.2)
province:add_pop(clergymen, haitian, catholic, 100, 0.3)
province:add_pop(laborer, haitian, catholic, 100, 0.2)
province:add_pop(burgeoise, haitian, catholic, 100, 0.7)
province:add_nucleus(haiti)
province:give_to(haiti)

--------------------------------------------------------------
-- Continent: Americas
-- Subcontinent: Caribbean/Central America
-- Country: French Republic

province = Province:new{ ref_name = "saint_martin", color = 0xF9EED2 }
province.name = _("Saint-Martin")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, french, catholic, 100, 0.8)
province:add_pop(farmer, french, catholic, 5000, 0.4)
province:add_pop(soldier, french, catholic, 100, 0.7)
province:add_pop(craftsmen, french, catholic, 100, 0.8)
province:add_pop(bureaucrat, french, catholic, 100, 0.9)
province:add_pop(burgeoise, french, catholic, 100, 0.9)
province:add_pop(clergymen, french, catholic, 100, 0.9)
province:add_pop(laborer, french, catholic, 100, 0.5)
province:add_pop(burgeoise, french, catholic, 100, 0.9)
province:add_nucleus(france)
province:give_to(france)

province = Province:new{ ref_name = "guadeloupe", color = 0x99FFAD }
province.name = _("Guadeloupe")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, french, catholic, 100, 0.8)
province:add_pop(farmer, french, catholic, 5000, 0.4)
province:add_pop(soldier, french, catholic, 100, 0.7)
province:add_pop(craftsmen, french, catholic, 100, 0.8)
province:add_pop(bureaucrat, french, catholic, 100, 0.9)
province:add_pop(burgeoise, french, catholic, 100, 0.9)
province:add_pop(clergymen, french, catholic, 100, 0.9)
province:add_pop(laborer, french, catholic, 100, 0.5)
province:add_pop(burgeoise, french, catholic, 100, 0.9)
province:add_nucleus(france)
province:give_to(france)

province = Province:new{ ref_name = "martinique", color = 0xFF3F92 }
province.name = _("Martinique")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, french, catholic, 100, 0.8)
province:add_pop(farmer, french, catholic, 5000, 0.4)
province:add_pop(soldier, french, catholic, 100, 0.7)
province:add_pop(craftsmen, french, catholic, 100, 0.8)
province:add_pop(bureaucrat, french, catholic, 100, 0.9)
province:add_pop(burgeoise, french, catholic, 100, 0.9)
province:add_pop(clergymen, french, catholic, 100, 0.9)
province:add_pop(laborer, french, catholic, 100, 0.5)
province:add_pop(burgeoise, french, catholic, 100, 0.9)
province:add_nucleus(france)
province:give_to(france)

--------------------------------------------------------------
-- Continent: Americas
-- Subcontinent: Caribbean/Central America
-- Country: Kingdom of the Netherlands

province = Province:new{ ref_name = "sint_maarten", color = 0xC491FF }
province.name = _("Sint Maarten")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, dutch, catholic, 100, 0.8)
province:add_pop(farmer, dutch, catholic, 5000, 0.4)
province:add_pop(soldier, dutch, catholic, 100, 0.7)
province:add_pop(craftsmen, dutch, catholic, 100, 0.8)
province:add_pop(bureaucrat, dutch, catholic, 100, 0.9)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_pop(clergymen, dutch, catholic, 100, 0.9)
province:add_pop(laborer, dutch, catholic, 100, 0.5)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_nucleus(netherlands)
province:give_to(netherlands)

province = Province:new{ ref_name = "saba", color = 0xBD4CFF }
province.name = _("Saba")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, dutch, catholic, 100, 0.8)
province:add_pop(farmer, dutch, catholic, 5000, 0.4)
province:add_pop(soldier, dutch, catholic, 100, 0.7)
province:add_pop(craftsmen, dutch, catholic, 100, 0.8)
province:add_pop(bureaucrat, dutch, catholic, 100, 0.9)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_pop(clergymen, dutch, catholic, 100, 0.9)
province:add_pop(laborer, dutch, catholic, 100, 0.5)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_nucleus(netherlands)
province:give_to(netherlands)

province = Province:new{ ref_name = "bonaire", color = 0xffcb30 }
province.name = _("Bonaire")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, dutch, catholic, 100, 0.8)
province:add_pop(farmer, dutch, catholic, 5000, 0.4)
province:add_pop(soldier, dutch, catholic, 100, 0.7)
province:add_pop(craftsmen, dutch, catholic, 100, 0.8)
province:add_pop(bureaucrat, dutch, catholic, 100, 0.9)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_pop(clergymen, dutch, catholic, 100, 0.9)
province:add_pop(laborer, dutch, catholic, 100, 0.5)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_nucleus(netherlands)
province:give_to(netherlands)

province = Province:new{ ref_name = "curacao", color = 0x8CC4FF }
province.name = _("Curaçao")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, dutch, catholic, 100, 0.8)
province:add_pop(farmer, dutch, catholic, 5000, 0.4)
province:add_pop(soldier, dutch, catholic, 100, 0.7)
province:add_pop(craftsmen, dutch, catholic, 100, 0.8)
province:add_pop(bureaucrat, dutch, catholic, 100, 0.9)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_pop(clergymen, dutch, catholic, 100, 0.9)
province:add_pop(laborer, dutch, catholic, 100, 0.5)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_nucleus(netherlands)
province:give_to(netherlands)

province = Province:new{ ref_name = "aruba", color = 0xCEFFFA }
province.name = _("Aruba")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, dutch, catholic, 100, 0.8)
province:add_pop(farmer, dutch, catholic, 5000, 0.4)
province:add_pop(soldier, dutch, catholic, 100, 0.7)
province:add_pop(craftsmen, dutch, catholic, 100, 0.8)
province:add_pop(bureaucrat, dutch, catholic, 100, 0.9)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_pop(clergymen, dutch, catholic, 100, 0.9)
province:add_pop(laborer, dutch, catholic, 100, 0.5)
province:add_pop(burgeoise, dutch, catholic, 100, 0.9)
province:add_nucleus(netherlands)
province:give_to(netherlands)

--------------------------------------------------------------
-- Continent: Americas
-- Subcontinent: Caribbean/Central Aerica
-- Country: Kingdom of Sweden

-- Change to saint barthélemy when taken by french
province = Province:new{ ref_name = "sankt_barthélemy", color = 0xFF545F }
province.name = _("Sankt Barthélemy")
province:register()
province:add_industry(wheat_farm, russia)
province:add_pop(artisan, swedish, protestant, 100, 0.8)
province:add_pop(farmer, swedish, protestant, 5000, 0.4)
province:add_pop(soldier, swedish, protestant, 100, 0.7)
province:add_pop(craftsmen, swedish, protestant, 100, 0.8)
province:add_pop(bureaucrat, swedish, protestant, 100, 0.9)
province:add_pop(burgeoise, swedish, protestant, 100, 0.9)
province:add_pop(clergymen, swedish, protestant, 100, 0.9)
province:add_pop(laborer, swedish, protestant, 100, 0.5)
province:add_pop(burgeoise, swedish, protestant, 100, 0.9)
province:add_nucleus(sweden)
province:give_to(sweden)
