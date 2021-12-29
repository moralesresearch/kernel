// SPDX-License-Identifier: GPL-2.0-only
/*
 * TI Camera Access Layer (CAL) - Video Device
 *
 * Copyright (c) 2015-2020 Texas Instruments Inc.
 *
 * Authors:
 *	Benoit Parrot <bparrot@ti.com>
 *	Laurent Pinchart <laurent.pinchart@ideasonboard.com>
 */

<<<<<<< HEAD
=======
#include <linux/delay.h>
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#include <linux/ioctl.h>
#include <linux/pm_runtime.h>
#include <linux/videodev2.h>

#include <media/media-device.h>
#include <media/v4l2-common.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-core.h>
#include <media/videobuf2-dma-contig.h>

#include "cal.h"

<<<<<<< HEAD
=======
/* ------------------------------------------------------------------
 *	Format Handling
 * ------------------------------------------------------------------
 */

static const struct cal_fmt cal_formats[] = {
	{
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp		= 16,
	}, {
		.fourcc		= V4L2_PIX_FMT_UYVY,
		.code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.bpp		= 16,
	}, {
		.fourcc		= V4L2_PIX_FMT_YVYU,
		.code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.bpp		= 16,
	}, {
		.fourcc		= V4L2_PIX_FMT_VYUY,
		.code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.bpp		= 16,
	}, {
		.fourcc		= V4L2_PIX_FMT_RGB565, /* gggbbbbb rrrrrggg */
		.code		= MEDIA_BUS_FMT_RGB565_2X8_LE,
		.bpp		= 16,
	}, {
		.fourcc		= V4L2_PIX_FMT_RGB565X, /* rrrrrggg gggbbbbb */
		.code		= MEDIA_BUS_FMT_RGB565_2X8_BE,
		.bpp		= 16,
	}, {
		.fourcc		= V4L2_PIX_FMT_RGB555, /* gggbbbbb arrrrrgg */
		.code		= MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE,
		.bpp		= 16,
	}, {
		.fourcc		= V4L2_PIX_FMT_RGB555X, /* arrrrrgg gggbbbbb */
		.code		= MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE,
		.bpp		= 16,
	}, {
		.fourcc		= V4L2_PIX_FMT_RGB24, /* rgb */
		.code		= MEDIA_BUS_FMT_RGB888_2X12_LE,
		.bpp		= 24,
	}, {
		.fourcc		= V4L2_PIX_FMT_BGR24, /* bgr */
		.code		= MEDIA_BUS_FMT_RGB888_2X12_BE,
		.bpp		= 24,
	}, {
		.fourcc		= V4L2_PIX_FMT_RGB32, /* argb */
		.code		= MEDIA_BUS_FMT_ARGB8888_1X32,
		.bpp		= 32,
	}, {
		.fourcc		= V4L2_PIX_FMT_SBGGR8,
		.code		= MEDIA_BUS_FMT_SBGGR8_1X8,
		.bpp		= 8,
	}, {
		.fourcc		= V4L2_PIX_FMT_SGBRG8,
		.code		= MEDIA_BUS_FMT_SGBRG8_1X8,
		.bpp		= 8,
	}, {
		.fourcc		= V4L2_PIX_FMT_SGRBG8,
		.code		= MEDIA_BUS_FMT_SGRBG8_1X8,
		.bpp		= 8,
	}, {
		.fourcc		= V4L2_PIX_FMT_SRGGB8,
		.code		= MEDIA_BUS_FMT_SRGGB8_1X8,
		.bpp		= 8,
	}, {
		.fourcc		= V4L2_PIX_FMT_SBGGR10,
		.code		= MEDIA_BUS_FMT_SBGGR10_1X10,
		.bpp		= 10,
	}, {
		.fourcc		= V4L2_PIX_FMT_SGBRG10,
		.code		= MEDIA_BUS_FMT_SGBRG10_1X10,
		.bpp		= 10,
	}, {
		.fourcc		= V4L2_PIX_FMT_SGRBG10,
		.code		= MEDIA_BUS_FMT_SGRBG10_1X10,
		.bpp		= 10,
	}, {
		.fourcc		= V4L2_PIX_FMT_SRGGB10,
		.code		= MEDIA_BUS_FMT_SRGGB10_1X10,
		.bpp		= 10,
	}, {
		.fourcc		= V4L2_PIX_FMT_SBGGR12,
		.code		= MEDIA_BUS_FMT_SBGGR12_1X12,
		.bpp		= 12,
	}, {
		.fourcc		= V4L2_PIX_FMT_SGBRG12,
		.code		= MEDIA_BUS_FMT_SGBRG12_1X12,
		.bpp		= 12,
	}, {
		.fourcc		= V4L2_PIX_FMT_SGRBG12,
		.code		= MEDIA_BUS_FMT_SGRBG12_1X12,
		.bpp		= 12,
	}, {
		.fourcc		= V4L2_PIX_FMT_SRGGB12,
		.code		= MEDIA_BUS_FMT_SRGGB12_1X12,
		.bpp		= 12,
	},
};

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
/*  Print Four-character-code (FOURCC) */
static char *fourcc_to_str(u32 fmt)
{
	static char code[5];

	code[0] = (unsigned char)(fmt & 0xff);
	code[1] = (unsigned char)((fmt >> 8) & 0xff);
	code[2] = (unsigned char)((fmt >> 16) & 0xff);
	code[3] = (unsigned char)((fmt >> 24) & 0xff);
	code[4] = '\0';

	return code;
}

/* ------------------------------------------------------------------
 *	V4L2 Video IOCTLs
 * ------------------------------------------------------------------
 */

<<<<<<< HEAD
static const struct cal_format_info *find_format_by_pix(struct cal_ctx *ctx,
							u32 pixelformat)
{
	const struct cal_format_info *fmtinfo;
	unsigned int k;

	for (k = 0; k < ctx->num_active_fmt; k++) {
		fmtinfo = ctx->active_fmt[k];
		if (fmtinfo->fourcc == pixelformat)
			return fmtinfo;
=======
static const struct cal_fmt *find_format_by_pix(struct cal_ctx *ctx,
						u32 pixelformat)
{
	const struct cal_fmt *fmt;
	unsigned int k;

	for (k = 0; k < ctx->num_active_fmt; k++) {
		fmt = ctx->active_fmt[k];
		if (fmt->fourcc == pixelformat)
			return fmt;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}

	return NULL;
}

<<<<<<< HEAD
static const struct cal_format_info *find_format_by_code(struct cal_ctx *ctx,
							 u32 code)
{
	const struct cal_format_info *fmtinfo;
	unsigned int k;

	for (k = 0; k < ctx->num_active_fmt; k++) {
		fmtinfo = ctx->active_fmt[k];
		if (fmtinfo->code == code)
			return fmtinfo;
=======
static const struct cal_fmt *find_format_by_code(struct cal_ctx *ctx,
						 u32 code)
{
	const struct cal_fmt *fmt;
	unsigned int k;

	for (k = 0; k < ctx->num_active_fmt; k++) {
		fmt = ctx->active_fmt[k];
		if (fmt->code == code)
			return fmt;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}

	return NULL;
}

static int cal_querycap(struct file *file, void *priv,
			struct v4l2_capability *cap)
{
	struct cal_ctx *ctx = video_drvdata(file);

	strscpy(cap->driver, CAL_MODULE_NAME, sizeof(cap->driver));
	strscpy(cap->card, CAL_MODULE_NAME, sizeof(cap->card));

	snprintf(cap->bus_info, sizeof(cap->bus_info),
		 "platform:%s", dev_name(ctx->cal->dev));
	return 0;
}

static int cal_enum_fmt_vid_cap(struct file *file, void  *priv,
				struct v4l2_fmtdesc *f)
{
	struct cal_ctx *ctx = video_drvdata(file);
<<<<<<< HEAD
	const struct cal_format_info *fmtinfo;
=======
	const struct cal_fmt *fmt;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	if (f->index >= ctx->num_active_fmt)
		return -EINVAL;

<<<<<<< HEAD
	fmtinfo = ctx->active_fmt[f->index];

	f->pixelformat = fmtinfo->fourcc;
=======
	fmt = ctx->active_fmt[f->index];

	f->pixelformat = fmt->fourcc;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	return 0;
}

static int __subdev_get_format(struct cal_ctx *ctx,
			       struct v4l2_mbus_framefmt *fmt)
{
	struct v4l2_subdev_format sd_fmt;
	struct v4l2_mbus_framefmt *mbus_fmt = &sd_fmt.format;
	int ret;

	sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	sd_fmt.pad = 0;

	ret = v4l2_subdev_call(ctx->phy->sensor, pad, get_fmt, NULL, &sd_fmt);
	if (ret)
		return ret;

	*fmt = *mbus_fmt;

	ctx_dbg(1, ctx, "%s %dx%d code:%04X\n", __func__,
		fmt->width, fmt->height, fmt->code);

	return 0;
}

static int __subdev_set_format(struct cal_ctx *ctx,
			       struct v4l2_mbus_framefmt *fmt)
{
	struct v4l2_subdev_format sd_fmt;
	struct v4l2_mbus_framefmt *mbus_fmt = &sd_fmt.format;
	int ret;

	sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	sd_fmt.pad = 0;
	*mbus_fmt = *fmt;

	ret = v4l2_subdev_call(ctx->phy->sensor, pad, set_fmt, NULL, &sd_fmt);
	if (ret)
		return ret;

	ctx_dbg(1, ctx, "%s %dx%d code:%04X\n", __func__,
		fmt->width, fmt->height, fmt->code);

	return 0;
}

<<<<<<< HEAD
static void cal_calc_format_size(struct cal_ctx *ctx,
				 const struct cal_format_info *fmtinfo,
				 struct v4l2_format *f)
{
	u32 bpl, max_width;

=======
static int cal_calc_format_size(struct cal_ctx *ctx,
				const struct cal_fmt *fmt,
				struct v4l2_format *f)
{
	u32 bpl, max_width;

	if (!fmt) {
		ctx_dbg(3, ctx, "No cal_fmt provided!\n");
		return -EINVAL;
	}

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	/*
	 * Maximum width is bound by the DMA max width in bytes.
	 * We need to recalculate the actual maxi width depending on the
	 * number of bytes per pixels required.
	 */
<<<<<<< HEAD
	max_width = CAL_MAX_WIDTH_BYTES / (ALIGN(fmtinfo->bpp, 8) >> 3);
	v4l_bound_align_image(&f->fmt.pix.width, 48, max_width, 2,
			      &f->fmt.pix.height, 32, CAL_MAX_HEIGHT_LINES,
			      0, 0);

	bpl = (f->fmt.pix.width * ALIGN(fmtinfo->bpp, 8)) >> 3;
=======
	max_width = MAX_WIDTH_BYTES / (ALIGN(fmt->bpp, 8) >> 3);
	v4l_bound_align_image(&f->fmt.pix.width, 48, max_width, 2,
			      &f->fmt.pix.height, 32, MAX_HEIGHT_LINES, 0, 0);

	bpl = (f->fmt.pix.width * ALIGN(fmt->bpp, 8)) >> 3;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	f->fmt.pix.bytesperline = ALIGN(bpl, 16);

	f->fmt.pix.sizeimage = f->fmt.pix.height *
			       f->fmt.pix.bytesperline;

	ctx_dbg(3, ctx, "%s: fourcc: %s size: %dx%d bpl:%d img_size:%d\n",
		__func__, fourcc_to_str(f->fmt.pix.pixelformat),
		f->fmt.pix.width, f->fmt.pix.height,
		f->fmt.pix.bytesperline, f->fmt.pix.sizeimage);
<<<<<<< HEAD
=======

	return 0;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static int cal_g_fmt_vid_cap(struct file *file, void *priv,
			     struct v4l2_format *f)
{
	struct cal_ctx *ctx = video_drvdata(file);

	*f = ctx->v_fmt;

	return 0;
}

static int cal_try_fmt_vid_cap(struct file *file, void *priv,
			       struct v4l2_format *f)
{
	struct cal_ctx *ctx = video_drvdata(file);
<<<<<<< HEAD
	const struct cal_format_info *fmtinfo;
	struct v4l2_subdev_frame_size_enum fse;
	int ret, found;

	fmtinfo = find_format_by_pix(ctx, f->fmt.pix.pixelformat);
	if (!fmtinfo) {
=======
	const struct cal_fmt *fmt;
	struct v4l2_subdev_frame_size_enum fse;
	int ret, found;

	fmt = find_format_by_pix(ctx, f->fmt.pix.pixelformat);
	if (!fmt) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		ctx_dbg(3, ctx, "Fourcc format (0x%08x) not found.\n",
			f->fmt.pix.pixelformat);

		/* Just get the first one enumerated */
<<<<<<< HEAD
		fmtinfo = ctx->active_fmt[0];
		f->fmt.pix.pixelformat = fmtinfo->fourcc;
=======
		fmt = ctx->active_fmt[0];
		f->fmt.pix.pixelformat = fmt->fourcc;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}

	f->fmt.pix.field = ctx->v_fmt.fmt.pix.field;

	/* check for/find a valid width/height */
	ret = 0;
	found = false;
	fse.pad = 0;
<<<<<<< HEAD
	fse.code = fmtinfo->code;
=======
	fse.code = fmt->code;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	fse.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	for (fse.index = 0; ; fse.index++) {
		ret = v4l2_subdev_call(ctx->phy->sensor, pad, enum_frame_size,
				       NULL, &fse);
		if (ret)
			break;

		if ((f->fmt.pix.width == fse.max_width) &&
		    (f->fmt.pix.height == fse.max_height)) {
			found = true;
			break;
		} else if ((f->fmt.pix.width >= fse.min_width) &&
			 (f->fmt.pix.width <= fse.max_width) &&
			 (f->fmt.pix.height >= fse.min_height) &&
			 (f->fmt.pix.height <= fse.max_height)) {
			found = true;
			break;
		}
	}

	if (!found) {
		/* use existing values as default */
		f->fmt.pix.width = ctx->v_fmt.fmt.pix.width;
		f->fmt.pix.height =  ctx->v_fmt.fmt.pix.height;
	}

	/*
	 * Use current colorspace for now, it will get
	 * updated properly during s_fmt
	 */
	f->fmt.pix.colorspace = ctx->v_fmt.fmt.pix.colorspace;
<<<<<<< HEAD
	cal_calc_format_size(ctx, fmtinfo, f);
	return 0;
=======
	return cal_calc_format_size(ctx, fmt, f);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static int cal_s_fmt_vid_cap(struct file *file, void *priv,
			     struct v4l2_format *f)
{
	struct cal_ctx *ctx = video_drvdata(file);
	struct vb2_queue *q = &ctx->vb_vidq;
<<<<<<< HEAD
	struct v4l2_subdev_format sd_fmt = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.pad = CAL_CAMERARX_PAD_SINK,
	};
	const struct cal_format_info *fmtinfo;
=======
	const struct cal_fmt *fmt;
	struct v4l2_mbus_framefmt mbus_fmt;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	int ret;

	if (vb2_is_busy(q)) {
		ctx_dbg(3, ctx, "%s device busy\n", __func__);
		return -EBUSY;
	}

	ret = cal_try_fmt_vid_cap(file, priv, f);
	if (ret < 0)
		return ret;

<<<<<<< HEAD
	fmtinfo = find_format_by_pix(ctx, f->fmt.pix.pixelformat);

	v4l2_fill_mbus_format(&sd_fmt.format, &f->fmt.pix, fmtinfo->code);

	ret = __subdev_set_format(ctx, &sd_fmt.format);
=======
	fmt = find_format_by_pix(ctx, f->fmt.pix.pixelformat);

	v4l2_fill_mbus_format(&mbus_fmt, &f->fmt.pix, fmt->code);

	ret = __subdev_set_format(ctx, &mbus_fmt);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (ret)
		return ret;

	/* Just double check nothing has gone wrong */
<<<<<<< HEAD
	if (sd_fmt.format.code != fmtinfo->code) {
=======
	if (mbus_fmt.code != fmt->code) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		ctx_dbg(3, ctx,
			"%s subdev changed format on us, this should not happen\n",
			__func__);
		return -EINVAL;
	}

<<<<<<< HEAD
	v4l2_fill_pix_format(&ctx->v_fmt.fmt.pix, &sd_fmt.format);
	ctx->v_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ctx->v_fmt.fmt.pix.pixelformat = fmtinfo->fourcc;
	ctx->v_fmt.fmt.pix.field = sd_fmt.format.field;
	cal_calc_format_size(ctx, fmtinfo, &ctx->v_fmt);

	v4l2_subdev_call(&ctx->phy->subdev, pad, set_fmt, NULL, &sd_fmt);

	ctx->fmtinfo = fmtinfo;
=======
	v4l2_fill_pix_format(&ctx->v_fmt.fmt.pix, &mbus_fmt);
	ctx->v_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ctx->v_fmt.fmt.pix.pixelformat  = fmt->fourcc;
	cal_calc_format_size(ctx, fmt, &ctx->v_fmt);
	ctx->fmt = fmt;
	ctx->m_fmt = mbus_fmt;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	*f = ctx->v_fmt;

	return 0;
}

static int cal_enum_framesizes(struct file *file, void *fh,
			       struct v4l2_frmsizeenum *fsize)
{
	struct cal_ctx *ctx = video_drvdata(file);
<<<<<<< HEAD
	const struct cal_format_info *fmtinfo;
=======
	const struct cal_fmt *fmt;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct v4l2_subdev_frame_size_enum fse;
	int ret;

	/* check for valid format */
<<<<<<< HEAD
	fmtinfo = find_format_by_pix(ctx, fsize->pixel_format);
	if (!fmtinfo) {
=======
	fmt = find_format_by_pix(ctx, fsize->pixel_format);
	if (!fmt) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		ctx_dbg(3, ctx, "Invalid pixel code: %x\n",
			fsize->pixel_format);
		return -EINVAL;
	}

	fse.index = fsize->index;
	fse.pad = 0;
<<<<<<< HEAD
	fse.code = fmtinfo->code;
=======
	fse.code = fmt->code;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	fse.which = V4L2_SUBDEV_FORMAT_ACTIVE;

	ret = v4l2_subdev_call(ctx->phy->sensor, pad, enum_frame_size, NULL,
			       &fse);
	if (ret)
		return ret;

	ctx_dbg(1, ctx, "%s: index: %d code: %x W:[%d,%d] H:[%d,%d]\n",
		__func__, fse.index, fse.code, fse.min_width, fse.max_width,
		fse.min_height, fse.max_height);

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = fse.max_width;
	fsize->discrete.height = fse.max_height;

	return 0;
}

static int cal_enum_input(struct file *file, void *priv,
			  struct v4l2_input *inp)
{
	if (inp->index > 0)
		return -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	sprintf(inp->name, "Camera %u", inp->index);
	return 0;
}

static int cal_g_input(struct file *file, void *priv, unsigned int *i)
{
	*i = 0;
	return 0;
}

static int cal_s_input(struct file *file, void *priv, unsigned int i)
{
	return i > 0 ? -EINVAL : 0;
}

/* timeperframe is arbitrary and continuous */
static int cal_enum_frameintervals(struct file *file, void *priv,
				   struct v4l2_frmivalenum *fival)
{
	struct cal_ctx *ctx = video_drvdata(file);
<<<<<<< HEAD
	const struct cal_format_info *fmtinfo;
=======
	const struct cal_fmt *fmt;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct v4l2_subdev_frame_interval_enum fie = {
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

<<<<<<< HEAD
	fmtinfo = find_format_by_pix(ctx, fival->pixel_format);
	if (!fmtinfo)
		return -EINVAL;

	fie.code = fmtinfo->code;
=======
	fmt = find_format_by_pix(ctx, fival->pixel_format);
	if (!fmt)
		return -EINVAL;

	fie.code = fmt->code;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	ret = v4l2_subdev_call(ctx->phy->sensor, pad, enum_frame_interval,
			       NULL, &fie);
	if (ret)
		return ret;
	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.interval;

	return 0;
}

static const struct v4l2_file_operations cal_fops = {
	.owner		= THIS_MODULE,
	.open           = v4l2_fh_open,
	.release        = vb2_fop_release,
<<<<<<< HEAD
=======
	.read           = vb2_fop_read,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	.poll		= vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2, /* V4L2 ioctl handler */
	.mmap           = vb2_fop_mmap,
};

static const struct v4l2_ioctl_ops cal_ioctl_ops = {
	.vidioc_querycap      = cal_querycap,
	.vidioc_enum_fmt_vid_cap  = cal_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = cal_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap   = cal_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = cal_s_fmt_vid_cap,
	.vidioc_enum_framesizes   = cal_enum_framesizes,
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_create_bufs   = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf   = vb2_ioctl_prepare_buf,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_expbuf        = vb2_ioctl_expbuf,
	.vidioc_enum_input    = cal_enum_input,
	.vidioc_g_input       = cal_g_input,
	.vidioc_s_input       = cal_s_input,
	.vidioc_enum_frameintervals = cal_enum_frameintervals,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_log_status    = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
};

/* ------------------------------------------------------------------
 *	videobuf2 Operations
 * ------------------------------------------------------------------
 */

static int cal_queue_setup(struct vb2_queue *vq,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct cal_ctx *ctx = vb2_get_drv_priv(vq);
	unsigned int size = ctx->v_fmt.fmt.pix.sizeimage;

	if (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	if (*nplanes) {
		if (sizes[0] < size)
			return -EINVAL;
		size = sizes[0];
	}

	*nplanes = 1;
	sizes[0] = size;

	ctx_dbg(3, ctx, "nbuffers=%d, size=%d\n", *nbuffers, sizes[0]);

	return 0;
}

static int cal_buffer_prepare(struct vb2_buffer *vb)
{
	struct cal_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct cal_buffer *buf = container_of(vb, struct cal_buffer,
					      vb.vb2_buf);
	unsigned long size;

<<<<<<< HEAD
=======
	if (WARN_ON(!ctx->fmt))
		return -EINVAL;

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	size = ctx->v_fmt.fmt.pix.sizeimage;
	if (vb2_plane_size(vb, 0) < size) {
		ctx_err(ctx,
			"data will not fit into plane (%lu < %lu)\n",
			vb2_plane_size(vb, 0), size);
		return -EINVAL;
	}

	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, size);
	return 0;
}

static void cal_buffer_queue(struct vb2_buffer *vb)
{
	struct cal_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct cal_buffer *buf = container_of(vb, struct cal_buffer,
					      vb.vb2_buf);
<<<<<<< HEAD
	unsigned long flags;

	/* recheck locking */
	spin_lock_irqsave(&ctx->dma.lock, flags);
	list_add_tail(&buf->list, &ctx->dma.queue);
	spin_unlock_irqrestore(&ctx->dma.lock, flags);
}

static void cal_release_buffers(struct cal_ctx *ctx,
				enum vb2_buffer_state state)
{
	struct cal_buffer *buf, *tmp;

	/* Release all queued buffers. */
	spin_lock_irq(&ctx->dma.lock);

	list_for_each_entry_safe(buf, tmp, &ctx->dma.queue, list) {
		list_del(&buf->list);
		vb2_buffer_done(&buf->vb.vb2_buf, state);
	}

	if (ctx->dma.pending) {
		vb2_buffer_done(&ctx->dma.pending->vb.vb2_buf, state);
		ctx->dma.pending = NULL;
	}

	if (ctx->dma.active) {
		vb2_buffer_done(&ctx->dma.active->vb.vb2_buf, state);
		ctx->dma.active = NULL;
	}

	spin_unlock_irq(&ctx->dma.lock);
=======
	struct cal_dmaqueue *vidq = &ctx->vidq;
	unsigned long flags;

	/* recheck locking */
	spin_lock_irqsave(&ctx->slock, flags);
	list_add_tail(&buf->list, &vidq->active);
	spin_unlock_irqrestore(&ctx->slock, flags);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static int cal_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct cal_ctx *ctx = vb2_get_drv_priv(vq);
<<<<<<< HEAD
	struct cal_buffer *buf;
	dma_addr_t addr;
	int ret;

	spin_lock_irq(&ctx->dma.lock);
	buf = list_first_entry(&ctx->dma.queue, struct cal_buffer, list);
	ctx->dma.pending = buf;
	list_del(&buf->list);
	spin_unlock_irq(&ctx->dma.lock);

	addr = vb2_dma_contig_plane_dma_addr(&buf->vb.vb2_buf, 0);

	pm_runtime_get_sync(ctx->cal->dev);

	cal_ctx_set_dma_addr(ctx, addr);
	cal_ctx_start(ctx);

	ret = v4l2_subdev_call(&ctx->phy->subdev, video, s_stream, 1);
	if (ret)
		goto err;

=======
	struct cal_dmaqueue *dma_q = &ctx->vidq;
	struct cal_buffer *buf, *tmp;
	unsigned long addr;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&ctx->slock, flags);
	if (list_empty(&dma_q->active)) {
		spin_unlock_irqrestore(&ctx->slock, flags);
		ctx_dbg(3, ctx, "buffer queue is empty\n");
		return -EIO;
	}

	buf = list_entry(dma_q->active.next, struct cal_buffer, list);
	ctx->cur_frm = buf;
	ctx->next_frm = buf;
	list_del(&buf->list);
	spin_unlock_irqrestore(&ctx->slock, flags);

	addr = vb2_dma_contig_plane_dma_addr(&ctx->cur_frm->vb.vb2_buf, 0);
	ctx->sequence = 0;

	pm_runtime_get_sync(ctx->cal->dev);

	cal_ctx_csi2_config(ctx);
	cal_ctx_pix_proc_config(ctx);
	cal_ctx_wr_dma_config(ctx, ctx->v_fmt.fmt.pix.bytesperline,
			      ctx->v_fmt.fmt.pix.height);

	cal_camerarx_enable_irqs(ctx->phy);

	ret = cal_camerarx_start(ctx->phy, ctx->fmt);
	if (ret)
		goto err;

	cal_ctx_wr_dma_addr(ctx, addr);
	cal_camerarx_ppi_enable(ctx->phy);

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (cal_debug >= 4)
		cal_quickdump_regs(ctx->cal);

	return 0;

err:
<<<<<<< HEAD
	cal_ctx_stop(ctx);
	pm_runtime_put_sync(ctx->cal->dev);

	cal_release_buffers(ctx, VB2_BUF_STATE_QUEUED);
=======
	spin_lock_irqsave(&ctx->slock, flags);
	vb2_buffer_done(&ctx->cur_frm->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	ctx->cur_frm = NULL;
	ctx->next_frm = NULL;
	list_for_each_entry_safe(buf, tmp, &dma_q->active, list) {
		list_del(&buf->list);
		vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	}
	spin_unlock_irqrestore(&ctx->slock, flags);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	return ret;
}

static void cal_stop_streaming(struct vb2_queue *vq)
{
	struct cal_ctx *ctx = vb2_get_drv_priv(vq);
<<<<<<< HEAD

	cal_ctx_stop(ctx);

	v4l2_subdev_call(&ctx->phy->subdev, video, s_stream, 0);

	pm_runtime_put_sync(ctx->cal->dev);

	cal_release_buffers(ctx, VB2_BUF_STATE_ERROR);
=======
	struct cal_dmaqueue *dma_q = &ctx->vidq;
	struct cal_buffer *buf, *tmp;
	unsigned long timeout;
	unsigned long flags;
	bool dma_act;

	cal_camerarx_ppi_disable(ctx->phy);

	/* wait for stream and dma to finish */
	dma_act = true;
	timeout = jiffies + msecs_to_jiffies(500);
	while (dma_act && time_before(jiffies, timeout)) {
		msleep(50);

		spin_lock_irqsave(&ctx->slock, flags);
		dma_act = ctx->dma_act;
		spin_unlock_irqrestore(&ctx->slock, flags);
	}

	if (dma_act)
		ctx_err(ctx, "failed to disable dma cleanly\n");

	cal_camerarx_disable_irqs(ctx->phy);
	cal_camerarx_stop(ctx->phy);

	/* Release all active buffers */
	spin_lock_irqsave(&ctx->slock, flags);
	list_for_each_entry_safe(buf, tmp, &dma_q->active, list) {
		list_del(&buf->list);
		vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	}

	if (ctx->cur_frm == ctx->next_frm) {
		vb2_buffer_done(&ctx->cur_frm->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	} else {
		vb2_buffer_done(&ctx->cur_frm->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		vb2_buffer_done(&ctx->next_frm->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
	}
	ctx->cur_frm = NULL;
	ctx->next_frm = NULL;
	spin_unlock_irqrestore(&ctx->slock, flags);

	pm_runtime_put_sync(ctx->cal->dev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static const struct vb2_ops cal_video_qops = {
	.queue_setup		= cal_queue_setup,
	.buf_prepare		= cal_buffer_prepare,
	.buf_queue		= cal_buffer_queue,
	.start_streaming	= cal_start_streaming,
	.stop_streaming		= cal_stop_streaming,
	.wait_prepare		= vb2_ops_wait_prepare,
	.wait_finish		= vb2_ops_wait_finish,
};

/* ------------------------------------------------------------------
 *	V4L2 Initialization and Registration
 * ------------------------------------------------------------------
 */

static const struct video_device cal_videodev = {
	.name		= CAL_MODULE_NAME,
	.fops		= &cal_fops,
	.ioctl_ops	= &cal_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release_empty,
<<<<<<< HEAD
	.device_caps	= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING,
=======
	.device_caps	= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
			  V4L2_CAP_READWRITE,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

static int cal_ctx_v4l2_init_formats(struct cal_ctx *ctx)
{
	struct v4l2_subdev_mbus_code_enum mbus_code;
	struct v4l2_mbus_framefmt mbus_fmt;
<<<<<<< HEAD
	const struct cal_format_info *fmtinfo;
=======
	const struct cal_fmt *fmt;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	unsigned int i, j, k;
	int ret = 0;

	/* Enumerate sub device formats and enable all matching local formats */
<<<<<<< HEAD
	ctx->active_fmt = devm_kcalloc(ctx->cal->dev, cal_num_formats,
=======
	ctx->active_fmt = devm_kcalloc(ctx->cal->dev, ARRAY_SIZE(cal_formats),
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
				       sizeof(*ctx->active_fmt), GFP_KERNEL);
	ctx->num_active_fmt = 0;

	for (j = 0, i = 0; ret != -EINVAL; ++j) {

		memset(&mbus_code, 0, sizeof(mbus_code));
		mbus_code.index = j;
		mbus_code.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(ctx->phy->sensor, pad, enum_mbus_code,
				       NULL, &mbus_code);
		if (ret)
			continue;

		ctx_dbg(2, ctx,
			"subdev %s: code: %04x idx: %u\n",
			ctx->phy->sensor->name, mbus_code.code, j);

<<<<<<< HEAD
		for (k = 0; k < cal_num_formats; k++) {
			fmtinfo = &cal_formats[k];

			if (mbus_code.code == fmtinfo->code) {
				ctx->active_fmt[i] = fmtinfo;
				ctx_dbg(2, ctx,
					"matched fourcc: %s: code: %04x idx: %u\n",
					fourcc_to_str(fmtinfo->fourcc),
					fmtinfo->code, i);
=======
		for (k = 0; k < ARRAY_SIZE(cal_formats); k++) {
			const struct cal_fmt *fmt = &cal_formats[k];

			if (mbus_code.code == fmt->code) {
				ctx->active_fmt[i] = fmt;
				ctx_dbg(2, ctx,
					"matched fourcc: %s: code: %04x idx: %u\n",
					fourcc_to_str(fmt->fourcc),
					fmt->code, i);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
				ctx->num_active_fmt = ++i;
			}
		}
	}

	if (i == 0) {
		ctx_err(ctx, "No suitable format reported by subdev %s\n",
			ctx->phy->sensor->name);
		return -EINVAL;
	}

	ret = __subdev_get_format(ctx, &mbus_fmt);
	if (ret)
		return ret;

<<<<<<< HEAD
	fmtinfo = find_format_by_code(ctx, mbus_fmt.code);
	if (!fmtinfo) {
=======
	fmt = find_format_by_code(ctx, mbus_fmt.code);
	if (!fmt) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		ctx_dbg(3, ctx, "mbus code format (0x%08x) not found.\n",
			mbus_fmt.code);
		return -EINVAL;
	}

<<<<<<< HEAD
	/* Save current format */
	v4l2_fill_pix_format(&ctx->v_fmt.fmt.pix, &mbus_fmt);
	ctx->v_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ctx->v_fmt.fmt.pix.pixelformat = fmtinfo->fourcc;
	ctx->v_fmt.fmt.pix.field = mbus_fmt.field;
	cal_calc_format_size(ctx, fmtinfo, &ctx->v_fmt);
	ctx->fmtinfo = fmtinfo;
=======
	/* Save current subdev format */
	v4l2_fill_pix_format(&ctx->v_fmt.fmt.pix, &mbus_fmt);
	ctx->v_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ctx->v_fmt.fmt.pix.pixelformat  = fmt->fourcc;
	cal_calc_format_size(ctx, fmt, &ctx->v_fmt);
	ctx->fmt = fmt;
	ctx->m_fmt = mbus_fmt;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return 0;
}

int cal_ctx_v4l2_register(struct cal_ctx *ctx)
{
	struct v4l2_ctrl_handler *hdl = &ctx->ctrl_handler;
	struct video_device *vfd = &ctx->vdev;
	int ret;

	ret = cal_ctx_v4l2_init_formats(ctx);
	if (ret)
		return ret;

	ret = v4l2_ctrl_add_handler(hdl, ctx->phy->sensor->ctrl_handler, NULL,
				    true);
	if (ret < 0) {
		ctx_err(ctx, "Failed to add sensor ctrl handler\n");
		return ret;
	}

	ret = video_register_device(vfd, VFL_TYPE_VIDEO, cal_video_nr);
	if (ret < 0) {
		ctx_err(ctx, "Failed to register video device\n");
		return ret;
	}

<<<<<<< HEAD
	ret = media_create_pad_link(&ctx->phy->subdev.entity,
				    CAL_CAMERARX_PAD_SOURCE,
				    &vfd->entity, 0,
				    MEDIA_LNK_FL_IMMUTABLE |
				    MEDIA_LNK_FL_ENABLED);
	if (ret) {
		ctx_err(ctx, "Failed to create media link for context %u\n",
			ctx->index);
		video_unregister_device(vfd);
		return ret;
	}

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	ctx_info(ctx, "V4L2 device registered as %s\n",
		 video_device_node_name(vfd));

	return 0;
}

void cal_ctx_v4l2_unregister(struct cal_ctx *ctx)
{
	ctx_dbg(1, ctx, "unregistering %s\n",
		video_device_node_name(&ctx->vdev));

	video_unregister_device(&ctx->vdev);
}

int cal_ctx_v4l2_init(struct cal_ctx *ctx)
{
	struct v4l2_ctrl_handler *hdl = &ctx->ctrl_handler;
	struct video_device *vfd = &ctx->vdev;
	struct vb2_queue *q = &ctx->vb_vidq;
	int ret;

<<<<<<< HEAD
	INIT_LIST_HEAD(&ctx->dma.queue);
	spin_lock_init(&ctx->dma.lock);
	mutex_init(&ctx->mutex);
	init_waitqueue_head(&ctx->dma.wait);

	/* Initialize the vb2 queue. */
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
=======
	INIT_LIST_HEAD(&ctx->vidq.active);
	spin_lock_init(&ctx->slock);
	mutex_init(&ctx->mutex);

	/* Initialize the vb2 queue. */
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_READ;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	q->drv_priv = ctx;
	q->buf_struct_size = sizeof(struct cal_buffer);
	q->ops = &cal_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &ctx->mutex;
	q->min_buffers_needed = 3;
	q->dev = ctx->cal->dev;

	ret = vb2_queue_init(q);
	if (ret)
		return ret;

	/* Initialize the video device and media entity. */
	*vfd = cal_videodev;
	vfd->v4l2_dev = &ctx->cal->v4l2_dev;
	vfd->queue = q;
	snprintf(vfd->name, sizeof(vfd->name), "CAL output %u", ctx->index);
	vfd->lock = &ctx->mutex;
	video_set_drvdata(vfd, ctx);

	ctx->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vfd->entity, 1, &ctx->pad);
	if (ret < 0)
		return ret;

	/* Initialize the control handler. */
	ret = v4l2_ctrl_handler_init(hdl, 11);
	if (ret < 0) {
		ctx_err(ctx, "Failed to init ctrl handler\n");
		goto error;
	}

	vfd->ctrl_handler = hdl;

	return 0;

error:
	media_entity_cleanup(&vfd->entity);
	return ret;
}

void cal_ctx_v4l2_cleanup(struct cal_ctx *ctx)
{
	v4l2_ctrl_handler_free(&ctx->ctrl_handler);
	media_entity_cleanup(&ctx->vdev.entity);
}
