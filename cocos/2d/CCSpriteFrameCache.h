/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __SPRITE_CCSPRITE_FRAME_CACHE_H__
#define __SPRITE_CCSPRITE_FRAME_CACHE_H__

/*
 * To create sprite frames and texture atlas, use this tool:
 * http://zwoptex.zwopple.com/
 */

#include "2d/CCSpriteFrame.h"
#include "2d/CCTexture2D.h"
#include "base/CCRef.h"
#include "base/CCValue.h"
#include "base/CCMap.h"

#include <set>
#include <string>

NS_CC_BEGIN

class Sprite;

/**
 * @addtogroup sprite_nodes
 * @{
 */

/** @brief Singleton that handles the loading of the sprite frames.
 精灵帧用它来存在缓存中.
 @since v0.9
 */
class CC_DLL SpriteFrameCache : public Ref
{
public:
    /** 这个一个共享单利返回一个精灵帧的缓存Returns the shared instance of the Sprite Frame cache */
    static SpriteFrameCache* getInstance(void);

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static SpriteFrameCache* sharedSpriteFrameCache() { return SpriteFrameCache::getInstance(); }

    /** 销毁这个缓存.他会释放所有的精灵帧和保留的实例*/
    static void destroyInstance();

    /** @deprecated Use destroyInstance() instead  */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedSpriteFrameCache() { return SpriteFrameCache::destroyInstance(); }

protected:
    // MARMALADE: Made this protected not private, as deriving from this class is pretty useful
    SpriteFrameCache(){}

public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SpriteFrameCache();
    bool init(void);

public:
    /** 从plist文件添加多个精灵帧。
     * 这个纹理将被自动装载。纹理名称将被.plist和.png的后缀取代。
     * 如果您想要使用另一个纹理,您应该使用addSpriteFramesWithFile(const std::string& plist,const std::string& textureFileName)方法。
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist);

    /** 从plist文件添加多个精灵帧，这个纹理将会被创建为与之相联系的精灵帧。
     @since v0.99.5
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName);

    /** 从plist文件添加多个精灵帧，这个纹理将会被创建为与之相联系的精灵帧。
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string&plist, Texture2D *texture);

    /** 添加一个精灵帧并给它附上一个名字.
     If the name already exists, then the contents of the old name will be replaced with the new one.
     */
    void addSpriteFrame(SpriteFrame *frame, const std::string& frameName);

    /** 清除这个字典里面加载过的精灵帧.
     * 当你的遇到"内存警告"你可以调用这个回收方法。
     * 在使用它短期内：它将释放一些不使用的资源来防止程序被强制关闭。
     * 在过程中:它将合理分配更多的资源。
     * 在长时间:它将是相同的。
     */
    void removeSpriteFrames();

    /** 删除从未被使用过的精灵帧.
     * 精灵帧的计数器变为1时将会被删除.
     * 在打开一个新的场景时（场景切换时），适合调用这个方法.
     */
    void removeUnusedSpriteFrames();

    /** 在精灵缓存中删除一个精灵帧*/
    void removeSpriteFrameByName(const std::string& name);

    /** 从plist文件中删除多个精灵帧.
    * 精灵帧存在的这个的文件将会被删除.
    * 当一个特殊的纹理需要被删除时，适合调用这个方法.
    * @since v0.99.5
    */
    void removeSpriteFramesFromFile(const std::string& plist);

    /** 删除被指定纹理的所有精灵帧.
     * 当一个特殊的纹理需要被删除时，适合调用这个方法.
     * @since v0.995.
     */
    void removeSpriteFramesFromTexture(Texture2D* texture);

    /** 返回一个之前添加的精灵帧.
     如果没有找到这个精灵帧的名字那么将返回nil.
     如果你要使用它你应该将返回的对象保存.
     * @js getSpriteFrame
     * @lua getSpriteFrame
     */
    SpriteFrame* getSpriteFrameByName(const std::string& name);

    /** @deprecated use getSpriteFrameByName() instead */
    CC_DEPRECATED_ATTRIBUTE SpriteFrame* spriteFrameByName(const std::string&name) { return getSpriteFrameByName(name); }

private:
    /*添加多个精灵帧到这个字典集合中，同样纹理将会被创建为与之关联的精灵帧.
     */
    void addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture);

    /** 从字典集合中删除多个精灵帧.
    * @since v0.99.5
    */
    void removeSpriteFramesFromDictionary(ValueMap& dictionary);

protected:
    Map<std::string, SpriteFrame*> _spriteFrames;
    ValueMap _spriteFramesAliases;
    std::set<std::string>*  _loadedFileNames;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __SPRITE_CCSPRITE_FRAME_CACHE_H__
