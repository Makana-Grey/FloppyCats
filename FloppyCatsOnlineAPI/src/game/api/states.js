import Router from 'koa-router'
import { setIsPlay, setIsPublic } from '../logic/playerStates.js'

const router = new Router()

/**
 * @param {{name: String; token: String; isPlay: Boolean}}
 */
router.put('/play', (ctx, next) => {
    if (setIsPlay(ctx.request.body)) {
        ctx.response.status = 200
    } else {
        ctx.response.status = 400
        ctx.response.body = `Can't set playing status`
    }

    next()
})

/**
 * @param {{name: String; token: String; isPublic: Boolean}}
 */
router.put('/public', (ctx, next) => {
    if (setIsPublic(ctx.request.body)) {
        ctx.response.status = 200
    } else {
        ctx.response.status = 400
        ctx.response.body = `Can't set public status`
    }

    next()
})

export default router.routes()
