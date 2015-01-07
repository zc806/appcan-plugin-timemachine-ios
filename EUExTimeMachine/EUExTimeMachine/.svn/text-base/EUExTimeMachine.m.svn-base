//
//  EUExTimeMachine.m
//  EUExTimeMachine
//
//  Created by AppCan on 13-4-10.
//  Copyright (c) 2013年 AppCan. All rights reserved.
//

#import "EUExTimeMachine.h"
#import "iCarousel_TimeMachine.h"
#import "EUtility.h"
#import "JSON.h"
#import "ReflectionView_T.h"
#define NUMBER_OF_VISIBLE_ITEMS 25
#define ITEM_SPACING 210.0f
#define INCLUDE_PLACEHOLDERS YES
@implementation EUExTimeMachine
@synthesize dataArray;
@synthesize itemsArray;
-(id)initWithBrwView:(EBrowserView *)eInBrwView{
    if (self = [super initWithBrwView:eInBrwView]) {
        
    }
    return self;
}
-(void)clean{
    [self close:nil];
    if (self.dataArray) {
        self.dataArray = nil;
    }
    if (self.itemsArray) {
        self.itemsArray = nil;
    }
    if (pageControl) {
        [pageControl release];
        pageControl = nil;
    }
}
-(void)dealloc{
    [self close:nil];
    if (self.dataArray) {
        self.dataArray = nil;
    }
    if (self.itemsArray) {
        self.itemsArray = nil;
    }
    if (pageControl) {
        [pageControl release];
        pageControl = nil;
    }
    [super dealloc];
}
-(void)open:(NSMutableArray *)array{
    float x,y,width,height;
    NSString *strId = nil;
    if ([array count]>0&&[array count]<8) {
        strId = [NSString stringWithFormat:@"%@",[array objectAtIndex:0]];
        
        for (UIContainsiCarouselView *iCarouselView in self.dataArray) {
            if (iCarouselView!=nil&&[iCarouselView isKindOfClass:[UIContainsiCarouselView class]]&&[iCarouselView.stringId isEqualToString:strId]) {
                for (UIView *subView in [iCarouselView subviews]) {
                    [subView removeFromSuperview];
                }
                [iCarouselView removeFromSuperview];
            }
        }
        x = [[array objectAtIndex:1] floatValue];
        y = [[array objectAtIndex:2] floatValue];
        width = [[array objectAtIndex:3] floatValue];
        height = [[array objectAtIndex:4] floatValue];

        if (!self.dataArray) {
            self.dataArray = [NSMutableArray arrayWithCapacity:1];
        }
        if ([self.dataArray count]>0) {
            [self.dataArray removeAllObjects];
        }
        CGRect rect = CGRectMake(x, y, width, height);
        UIContainsiCarouselView *tempView = [[UIContainsiCarouselView alloc] initWithFrame:rect];
        [tempView setBackgroundColor:[UIColor clearColor]];
        [tempView setStringId:strId];
    
        iCarousel_TimeMachine *carousel = [[iCarousel_TimeMachine alloc] initWithFrame:CGRectMake(x, 0, width, height)];
        carousel.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        carousel.type = iCarouselTypeRotary;
        carousel.delegate = self;
        carousel.dataSource = self;
        carousel.decelerationRate = 0.5;
        carousel.viewpointOffset = CGSizeMake(rect.size.width, -rect.size.height);
        carousel.contentOffset=CGSizeMake(rect.size.width,-rect.size.height);
        carousel.strId = strId;
        [carousel setBackgroundColor:[UIColor clearColor]];
        [tempView addSubview:carousel];
        if (![self.dataArray containsObject:tempView]) {
            [self.dataArray addObject:tempView];
            pageControl = [[StyledPageControl_T alloc] initWithFrame:CGRectMake(carousel.frame.origin.x,y+height-50,width,50)];
            pageControl.hidesForSinglePage = YES;
            pageControl.userInteractionEnabled=NO;
            pageControl.backgroundColor = [UIColor clearColor];
            //设置页数及当前显示页数
            //[pageControl setNumberOfPages:2];
            [pageControl setCurrentPage:0];
            [pageControl setPageControlStyle:PageControlStyleThumb];
             NSString *path_1 = [[NSBundle mainBundle] pathForResource:@"uexTimeMachine/1" ofType:@"png"];
            UIImage *imageNomal = [UIImage imageWithContentsOfFile:path_1];
            NSString *path_2 = [[NSBundle mainBundle] pathForResource:@"uexTimeMachine/2" ofType:@"png"];
            UIImage *imageSelected = [UIImage imageWithContentsOfFile:path_2];
            [pageControl setThumbImage:imageNomal];
            [pageControl setSelectedThumbImage:imageSelected];
            [tempView addSubview:pageControl];
            [EUtility brwView:self.meBrwView addSubview:tempView];
        }
        [tempView release];
        [carousel release];
        NSString *jsstr = [NSString stringWithFormat:@"if(uexTimeMachine.loadData!=null){uexTimeMachine.loadData('%@')}",strId];
        [EUtility brwView:meBrwView evaluateScript:jsstr];
        NSString *jsstrCB = [NSString stringWithFormat:@"if(uexTimeMachine.cbOpen!=null){uexTimeMachine.cbOpen('%@')}",strId];
        [EUtility brwView:meBrwView evaluateScript:jsstrCB];
    }
    
}
-(void)setJsonData:(NSMutableArray *)array{
    if ([array count]==0) {
        return;
    }
    NSString *string = [array objectAtIndex:0];
    NSDictionary *jsonDict = [string JSONValue];
    if (!jsonDict) {
        return;
    }
    if (!self.itemsArray) {
        self.itemsArray = [NSMutableArray arrayWithCapacity:1];
    }
    if ([self.itemsArray count]>0) {
        [self.itemsArray removeAllObjects];
    }
    [self.itemsArray addObjectsFromArray:[jsonDict objectForKey:@"data"]];//添加数据
    int numberOfPages = (int)[self.itemsArray count];
    //设置页数及当前显示页数
    [pageControl setNumberOfPages:numberOfPages];
    NSString *idString = [NSString stringWithFormat:@"%@",[jsonDict objectForKey:@"id"]];
            NSDictionary *dict =[[jsonDict objectForKey:@"data"] objectAtIndex:0];
            NSString *url = [self absPath:[dict objectForKey:@"imageUrl"]];
            UIImage *urlImage =[UIImage imageWithContentsOfFile:url];
    int x=0;
    int y=0;
    if (self.dataArray) {
        for (UIContainsiCarouselView *iCarouselView in self.dataArray) {
            if ([iCarouselView.stringId isEqualToString:idString]) {
                for (UIView *subView in [iCarouselView subviews]) {
                    if (subView!=nil&&[subView isKindOfClass:[iCarousel_TimeMachine class]]) {
                        iCarousel_TimeMachine *icarousel =(iCarousel_TimeMachine *)subView;
                        x = (icarousel.frame.size.width-urlImage.size.width/2)/2;
                        y = (icarousel.frame.size.height-urlImage.size.height/2)/2;
                        if (icarousel) {
                            [icarousel setFrame:CGRectMake(x,y, urlImage.size.width/2, urlImage.size.height/2)];
                            [icarousel reloadData];
                        }
                    }else{
                        StyledPageControl_T *page = (StyledPageControl_T *)subView;
                        if (page) {
                            [page setFrame:CGRectMake(x, y+urlImage.size.height/2, urlImage.size.width/2, 50)];
                            [page setCurrentPage:0];
                        }
                    }
                }
            }            
        }
    }
}
-(void)close:(NSMutableArray *)array{
    if ([array count]>0) {
        NSString *IdStr = [array objectAtIndex:0];
        NSArray *IdArray = [IdStr componentsSeparatedByString:@","];
        if (self.dataArray) {
            for (NSString *stringId in IdArray) {
                for (UIContainsiCarouselView *iCarouselView in self.dataArray) {
                    if (iCarouselView!=nil&&[iCarouselView isKindOfClass:[UIContainsiCarouselView class]]&&[iCarouselView.stringId isEqualToString:stringId]) {
                        for (UIView *subView in [iCarouselView subviews]) {
                            [subView removeFromSuperview];
                        }
                        [iCarouselView removeFromSuperview];
                    }
                }
            }
            if ([self.dataArray count]>0) {
                [self.dataArray removeAllObjects];
            }
            self.dataArray = nil;
        }
    }else{
        //全部移除
        if (self.dataArray) {
            for (UIContainsiCarouselView *iCarouselView in self.dataArray) {
                    [iCarouselView removeFromSuperview];
                }
            if ([self.dataArray count]>0) {
                [self.dataArray removeAllObjects];
            }
            self.dataArray = nil;
        }
    }
}
#pragma mark -
#pragma mark iCarousel methods

- (NSUInteger)numberOfItemsInCarousel:(iCarousel_TimeMachine *)carousel
{   if([self.itemsArray count]>0){
        return [self.itemsArray count];
    }
    return 0;
}

- (NSUInteger)numberOfVisibleItemsInCarousel:(iCarousel_TimeMachine *)carousel
{
    //limit the number of items views loaded concurrently (for performance reasons)
    if([self.itemsArray count]>0){
        return [self.itemsArray count];
    }
    return 1;
}

- (UIView *)carousel:(iCarousel_TimeMachine *)carousel viewForItemAtIndex:(NSUInteger)index reusingView:(ReflectionView_T *)view
{
    if ([self.itemsArray count]>0) {
        UILabel *label = nil;
        //create new view if no view is available for recycling
        if (view == nil)
        {
            NSDictionary *dict = [self.itemsArray objectAtIndex:index];
            NSString *url = [self absPath:[dict objectForKey:@"imageUrl"]];
            view = [[[ReflectionView_T alloc] initWithFrame:CGRectMake(0, 0, carousel.frame.size.width, carousel.frame.size.height)] autorelease];
            label = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, view.bounds.size.width, 45)] autorelease];
            label.backgroundColor = [UIColor clearColor];
            label.textAlignment = UITextAlignmentLeft;
            label.font = [label.font fontWithSize:25];
            [view setImage:[UIImage imageWithContentsOfFile:url]];
            [view addSubview:label];
        }
        else
        {
            label = [[view subviews] lastObject];
        }
        //set label
        label.text = [[self.itemsArray objectAtIndex:index] objectForKey:@"title"];
        return view;
    }
    return nil;
}

- (NSUInteger)numberOfPlaceholdersInCarousel:(iCarousel_TimeMachine *)carousel
{
	//note: placeholder views are only displayed if wrapping is disabled
	return INCLUDE_PLACEHOLDERS? 2: 0;
}

- (UIView *)carousel:(iCarousel_TimeMachine *)carousel placeholderViewAtIndex:(NSUInteger)index reusingView:(ReflectionView_T *)view
{
    if ([self.itemsArray count]>0) {
        UILabel *label = nil;
        
        //create new view if no view is available for recycling
        if (view == nil)
        {
            NSDictionary *dict = [self.itemsArray objectAtIndex:index];
            NSString *url = [self absPath:[dict objectForKey:@"imageUrl"]];
            view = [[[ReflectionView_T alloc] initWithFrame:CGRectMake(0, 0, carousel.frame.size.width, carousel.frame.size.height)] autorelease];
               label = [[[UILabel alloc] initWithFrame:view.bounds] autorelease];
            label.backgroundColor = [UIColor clearColor];
            label.textAlignment = UITextAlignmentCenter;
            label.font = [label.font fontWithSize:50.0f];
            [view setImage:[UIImage imageWithContentsOfFile:url]];
            [view addSubview:label];
        }
        else
        {
            label = [[view subviews] lastObject];
        }
        
        //set label
        label.text = (index == 0)? @"[": @"]";
        return view;
    }
    return nil;
}

- (CGFloat)carouselItemWidth:(iCarousel_TimeMachine *)carousel
{
    //slightly wider than item view
    return carousel.frame.size.width/4;
}

- (CGFloat)carousel:(iCarousel_TimeMachine *)carousel itemAlphaForOffset:(CGFloat)offset
{
	//set opacity based on distance from camera
    return 1.0f - fminf(fmaxf(offset, 0.0f), 1.0f);
}

- (CATransform3D)carousel:(iCarousel_TimeMachine *)_carousel itemTransformForOffset:(CGFloat)offset baseTransform:(CATransform3D)transform
{
    //implement 'flip3D' style carousel
    transform = CATransform3DRotate(transform, M_PI / 8.0f, 0.0f, 0.0f, 0.0f);
    return CATransform3DTranslate(transform, 0.0f, 0.0f, offset * _carousel.itemWidth);
}

- (BOOL)carouselShouldWrap:(iCarousel_TimeMachine *)carousel
{
    //wrap all carousels
    return YES;
}
-(void)carousel:(iCarousel_TimeMachine *)carousel didSelectItemAtIndex:(NSInteger)index{
    NSString *jsonString = [NSString stringWithFormat:@"if(uexTimeMachine.onItemSelected!=null){uexTimeMachine.onItemSelected('%@','%d')}",carousel.strId,index];
    [EUtility brwView:meBrwView evaluateScript:jsonString];
}
-(void)setPageIndex:(iCarousel_TimeMachine *)carousel{
    int currentItemIndex =carousel.currentItemIndex;
    for (UIContainsiCarouselView *iCarouselView in self.dataArray) {
        for (UIView *subView in [iCarouselView subviews]) {
            if (subView!=nil&&[subView isKindOfClass:[StyledPageControl_T class]]) {
                StyledPageControl_T *page = (StyledPageControl_T *)subView;
                if (page) {
                    [page setCurrentPage:currentItemIndex];
                }
            }
        }
    }
}
- (void)carouselWillBeginDragging:(iCarousel_TimeMachine *)carousel{
    [self setPageIndex:carousel];
}
- (void)carouselDidEndDragging:(iCarousel_TimeMachine *)carousel willDecelerate:(BOOL)decelerate{
    [self setPageIndex:carousel];

}
- (void)carouselWillBeginDecelerating:(iCarousel_TimeMachine *)carousel{
    
}
- (void)carouselDidEndDecelerating:(iCarousel_TimeMachine *)carousel{
    [self setPageIndex:carousel];
}
- (void)carouselDidEndScrollingAnimation:(iCarousel_TimeMachine *)carousel{
    [self setPageIndex:carousel];
}
@end
