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
--  	provinces/europe/britain.lua
--
-- 	Abstract:
--      Does important stuff
-- ----------------------------------------------------------------------------

local uk_provinces_list = {
   { ref_name = "province_e0343600", name = _("Unknown"), color = 0x3634e0 },
   { ref_name = "province_40fdd500", name = _("Unknown"), color = 0xd5fd40 },
   { ref_name = "province_60164800", name = _("Unknown"), color = 0x481660 },
   { ref_name = "province_e0194600", name = _("Unknown"), color = 0x4619e0 },
   { ref_name = "province_40623100", name = _("Unknown"), color = 0x316240 },
   { ref_name = "province_e091cc00", name = _("Unknown"), color = 0xcc91e0 },
   { ref_name = "province_60c2cd00", name = _("Unknown"), color = 0xcdc260 },
   { ref_name = "province_692d00", name = _("Unknown"), color = 0x2d6900 },
   { ref_name = "province_6098bb00", name = _("Unknown"), color = 0xbb9860 },
   { ref_name = "province_60093700", name = _("Unknown"), color = 0x370960 },
   { ref_name = "province_808b8400", name = _("Unknown"), color = 0x848b80 },
   { ref_name = "province_e0beba00", name = _("Unknown"), color = 0xbabee0 },
   { ref_name = "province_a0d72c00", name = _("Unknown"), color = 0x2cd7a0 },
   { ref_name = "province_80b52b00", name = _("Unknown"), color = 0x2bb580 },
   { ref_name = "province_e098d000", name = _("Unknown"), color = 0xd098e0 },
   { ref_name = "province_607d3600", name = _("Unknown"), color = 0x367d60 },
   { ref_name = "province_79a300", name = _("Unknown"), color = 0xa37900 },
   { ref_name = "province_a0b83e00", name = _("Unknown"), color = 0x3eb8a0 },
   { ref_name = "province_d85600", name = _("Unknown"), color = 0x56d800 },
   { ref_name = "province_c083c700", name = _("Unknown"), color = 0xc783c0 },
   { ref_name = "province_2014cc00", name = _("Unknown"), color = 0xcc1420 },
   { ref_name = "province_40922a00", name = _("Unknown"), color = 0x2a9240 },
   { ref_name = "province_20a73100", name = _("Unknown"), color = 0x31a720 },
   { ref_name = "province_60ec3500", name = _("Unknown"), color = 0x35ec60 },
   { ref_name = "province_a0bf3a00", name = _("Unknown"), color = 0x3abfa0 },
   { ref_name = "province_60c2cb00", name = _("Unknown"), color = 0xcbc260 },
   { ref_name = "province_40624600", name = _("Unknown"), color = 0x466240 },
   { ref_name = "province_808aae00", name = _("Unknown"), color = 0xae8a80 },
   { ref_name = "province_20e52400", name = _("Unknown"), color = 0x24e520 },
   { ref_name = "province_9d3900", name = _("Unknown"), color = 0x399d00 },
   { ref_name = "province_49aa00", name = _("Unknown"), color = 0xaa4900 },
   { ref_name = "province_20515f00", name = _("Unknown"), color = 0x5f5120 },
   { ref_name = "province_60aadb00", name = _("Unknown"), color = 0xdbaa60 },
   { ref_name = "province_337f00", name = _("Unknown"), color = 0x7f3300 },
   { ref_name = "province_262c7c00", name = _("Unknown"), color = 0x7c2c26 },
   { ref_name = "province_ff427a00", name = _("Unknown"), color = 0x7a42ff },
   { ref_name = "province_80bbd100", name = _("Unknown"), color = 0xd1bb80 },
   { ref_name = "province_c0153300", name = _("Unknown"), color = 0x3315c0 },
   { ref_name = "province_7c5e6000", name = _("Unknown"), color = 0x605e7c },
   { ref_name = "province_c0b85300", name = _("Unknown"), color = 0x53b8c0 },
   { ref_name = "province_c0aac800", name = _("Unknown"), color = 0xc8aac0 },
   { ref_name = "province_ff9eab00", name = _("Unknown"), color = 0xab9eff },
   { ref_name = "province_d68200", name = _("Unknown"), color = 0x82d600 },
   { ref_name = "province_d6baff00", name = _("Unknown"), color = 0xffbad6 },
   { ref_name = "province_e04a3f00", name = _("Unknown"), color = 0x3f4ae0 },
   { ref_name = "province_40194600", name = _("Unknown"), color = 0x461940 },
   { ref_name = "province_e2ffa500", name = _("Unknown"), color = 0xa5ffe2 },
   { ref_name = "province_2031cd00", name = _("Unknown"), color = 0xcd3120 },
   { ref_name = "province_e03b4700", name = _("Unknown"), color = 0x473be0 },
   { ref_name = "province_f3c600", name = _("Unknown"), color = 0xc6f300 },
   { ref_name = "province_e0c23800", name = _("Unknown"), color = 0x38c2e0 },
   { ref_name = "province_80b14200", name = _("Unknown"), color = 0x42b180 },
   { ref_name = "province_405aca00", name = _("Unknown"), color = 0xca5a40 },
   { ref_name = "province_e0c94900", name = _("Unknown"), color = 0x49c9e0 },
   { ref_name = "province_20f7ad00", name = _("Unknown"), color = 0xadf720 },
   { ref_name = "province_9cb900", name = _("Unknown"), color = 0xb99c00 },
   { ref_name = "province_a0a03700", name = _("Unknown"), color = 0x37a0a0 },
   { ref_name = "province_bbbc00", name = _("Unknown"), color = 0xbcbb00 },
   { ref_name = "province_80935400", name = _("Unknown"), color = 0x549380 },
   { ref_name = "province_c0072600", name = _("Unknown"), color = 0x2607c0 },
   { ref_name = "province_20d3c300", name = _("Unknown"), color = 0xc3d320 },
   { ref_name = "province_a0f07200", name = _("Unknown"), color = 0x72f0a0 },
   { ref_name = "province_8026d300", name = _("Unknown"), color = 0xd32680 },
   { ref_name = "province_c083e400", name = _("Unknown"), color = 0xe483c0 },
   { ref_name = "province_806fd300", name = _("Unknown"), color = 0xd36f80 },
   { ref_name = "province_60c5b600", name = _("Unknown"), color = 0xb6c560 },
   { ref_name = "province_a0149e00", name = _("Unknown"), color = 0x9e14a0 },
   { ref_name = "province_20312300", name = _("Unknown"), color = 0x233120 },
   { ref_name = "province_80d3c300", name = _("Unknown"), color = 0xc3d380 },
   { ref_name = "province_20ae2f00", name = _("Unknown"), color = 0x2fae20 },
   { ref_name = "province_c03eda00", name = _("Unknown"), color = 0xda3ec0 },
   { ref_name = "province_2076cf00", name = _("Unknown"), color = 0xcf7620 },
   { ref_name = "province_40513b00", name = _("Unknown"), color = 0x3b5140 },
   { ref_name = "province_8029bc00", name = _("Unknown"), color = 0xbc2980 },
   { ref_name = "province_dcd600", name = _("Unknown"), color = 0xd6dc00 },
   { ref_name = "province_208c5400", name = _("Unknown"), color = 0x548c20 },
   { ref_name = "province_600bd000", name = _("Unknown"), color = 0xd00b60 },
   { ref_name = "province_40e23b00", name = _("Unknown"), color = 0x3be240 },
   { ref_name = "province_c0ed3100", name = _("Unknown"), color = 0x31edc0 },
   { ref_name = "province_c03c3200", name = _("Unknown"), color = 0x323cc0 },
   { ref_name = "province_20beba00", name = _("Unknown"), color = 0xbabe20 },
   { ref_name = "province_a0e4b900", name = _("Unknown"), color = 0xb9e4a0 },
   { ref_name = "province_a0cc3200", name = _("Unknown"), color = 0x32cca0 },
   { ref_name = "province_a13500", name = _("Unknown"), color = 0x35a100 },
   { ref_name = "province_67b100", name = _("Unknown"), color = 0xb16700 },
   { ref_name = "province_a0b9bc00", name = _("Unknown"), color = 0xbcb9a0 },
   { ref_name = "province_6037d100", name = _("Unknown"), color = 0xd13760 },
   { ref_name = "province_60b2c000", name = _("Unknown"), color = 0xc0b260 },
   { ref_name = "province_803d4500", name = _("Unknown"), color = 0x453d80 },
   { ref_name = "province_a0d6c300", name = _("Unknown"), color = 0xc3d6a0 },
   { ref_name = "province_80988000", name = _("Unknown"), color = 0x809880 },
   { ref_name = "province_c07ae400", name = _("Unknown"), color = 0xe47ac0 },
   { ref_name = "province_c0a7ca00", name = _("Unknown"), color = 0xcaa7c0 },
   { ref_name = "province_80dd5400", name = _("Unknown"), color = 0x54dd80 },
   { ref_name = "province_e0dcd400", name = _("Unknown"), color = 0xd4dce0 },
   { ref_name = "province_6064c400", name = _("Unknown"), color = 0xc46460 },
   { ref_name = "province_de6100", name = _("Unknown"), color = 0x61de00 },
   { ref_name = "province_cb4700", name = _("Unknown"), color = 0x47cb00 },
   { ref_name = "province_809c2400", name = _("Unknown"), color = 0x249c80 },
   { ref_name = "province_a13b00", name = _("Unknown"), color = 0x3ba100 },
   { ref_name = "province_2062c800", name = _("Unknown"), color = 0xc86220 },
   { ref_name = "province_e0515000", name = _("Unknown"), color = 0x5051e0 },
   { ref_name = "province_806c4000", name = _("Unknown"), color = 0x406c80 },
   { ref_name = "province_200be500", name = _("Unknown"), color = 0xe50b20 },
   { ref_name = "province_c0f4b300", name = _("Unknown"), color = 0xb3f4c0 },
   { ref_name = "province_a0db3f00", name = _("Unknown"), color = 0x3fdba0 },
   { ref_name = "province_60a9ca00", name = _("Unknown"), color = 0xcaa960 },
   { ref_name = "province_a00f3700", name = _("Unknown"), color = 0x370fa0 },
   { ref_name = "province_e06aaf00", name = _("Unknown"), color = 0xaf6ae0 },
   { ref_name = "province_409ce300", name = _("Unknown"), color = 0xe39c40 },
   { ref_name = "province_a03bb200", name = _("Unknown"), color = 0xb23ba0 },
   { ref_name = "province_80434300", name = _("Unknown"), color = 0x434380 },
   { ref_name = "province_6037b400", name = _("Unknown"), color = 0xb43760 },
   { ref_name = "province_c063d900", name = _("Unknown"), color = 0xd963c0 },
   { ref_name = "province_1f9800", name = _("Unknown"), color = 0x981f00 },
   { ref_name = "province_543900", name = _("Unknown"), color = 0x395400 },
   { ref_name = "province_e0b14200", name = _("Unknown"), color = 0x42b1e0 },
   { ref_name = "province_c0499900", name = _("Unknown"), color = 0x9949c0 },
   { ref_name = "province_60dda800", name = _("Unknown"), color = 0xa8dd60 },
   { ref_name = "province_802e3a00", name = _("Unknown"), color = 0x3a2e80 },
   { ref_name = "province_6056b900", name = _("Unknown"), color = 0xb95660 },
   { ref_name = "province_a0e06000", name = _("Unknown"), color = 0x60e0a0 },
   { ref_name = "province_f3ffbd00", name = _("Unknown"), color = 0xbdfff3 },
   { ref_name = "province_80de2800", name = _("Unknown"), color = 0x28de80 },
   { ref_name = "province_6232ff00", name = _("Unknown"), color = 0xff3262 },
   { ref_name = "province_8306300", name = _("Unknown"), color = 0x633008 },
   { ref_name = "province_40090000", name = _("Unknown"), color = 0x940 },
   { ref_name = "province_a0a6f700", name = _("Unknown"), color = 0xf7a6a0 },
   { ref_name = "province_40048800", name = _("Unknown"), color = 0x880440 },
   { ref_name = "province_40e4c600", name = _("Unknown"), color = 0xc6e440 },
}

for k, v in pairs(uk_provinces_list) do
    province = Province:new(v)
    province:register()

    province:add_industry(wheat_farm, united_kingdom)
    province:add_pop(artisan, british, catholic, 5000, 0.9)
    province:add_pop(farmer, british, catholic, 40000, 0.8)
    province:add_pop(soldier, british, catholic, 8000, 0.8)
    province:add_pop(craftsmen, british, catholic, 5000, 0.9)
    province:add_pop(bureaucrat, british, catholic, 5000, 0.9)
    province:add_pop(burgeoise, british, catholic, 5000, 0.9)
    province:add_pop(clergymen, british, catholic, 5000, 0.9)
    province:add_pop(laborer, british, catholic, 50000, 0.8)
    province:add_pop(burgeoise, british, catholic, 800, 0.9)
    province:add_nucleus(united_kingdom)
    province:give_to(united_kingdom)
    province:set_terrain(plains)
end

