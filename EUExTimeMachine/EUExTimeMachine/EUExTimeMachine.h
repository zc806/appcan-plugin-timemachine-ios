//
//  EUExTimeMachine.h
//  EUExTimeMachine
//
//  Created by AppCan on 13-4-10.
//  Copyright (c) 2013年 AppCan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EUExBase.h"
#import "iCarousel_TimeMachine.h"
#import "UIContainsiCarouselView.h"
#import "StyledPageControl_T.h"
@interface EUExTimeMachine : EUExBase<iCarouselDelegate,iCarouselDataSource>{
    StyledPageControl_T *pageControl;
}
@property(nonatomic, retain) NSMutableArray *dataArray;
@property(nonatomic, retain) NSMutableArray *itemsArray;
//@property(nonatomic,retain)NSMutableArray *pageControllerArray;
@end
