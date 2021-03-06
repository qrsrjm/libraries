/******************************************************************************
 * Copyright (C) 2014-2018 Zhifeng Gong <gozfree@163.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with libraries; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 ******************************************************************************/
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <liblog.h>
#include "libgconfig.h"
using namespace std;

static void lua_test()
{
    LuaConfig *conf = Config::create("lua/config.lua");
    logi("yuv_path= %s\n", (*conf)["yuv_path"].get<string>("").c_str());
    logi("[type_3][sub_type_1][my] = %s\n",
         (*conf)["type_3"]["sub_type_1"]["my"].get<string>("").c_str());
    conf->destroy();
}

static void json_test()
{
    JsonConfig *conf = Config::create("json/config.json");
    logi("[name] = %s\n", (*conf)["name"].asString().c_str());

    Json::Value root;
    Json::Value name;
    name["name"] = "hello";
    name["age"] = 10;
    root.append(name);


    Json::FastWriter writer;
    std::string json_file = writer.write(root);
    ofstream ofs;
    ofs.open("test1.json");
    assert(ofs.is_open());
    ofs<<json_file;

    conf->destroy();
}

int main(int argc, char **argv)
{
    lua_test();
    json_test();
    return 0;
}
